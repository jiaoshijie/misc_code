package downloader

import (
  "fmt"
  "os"
  "time"
  "io"

  "github.com/jiaoshijie/dlbili/bilibili"
  "github.com/jiaoshijie/dlbili/request"
  "github.com/jiaoshijie/dlbili/utils"

  "github.com/cheggaaa/pb/v3"
)

type Downloader struct {
  Title string
  bar *pb.ProgressBar
}

func progressBar(size int64) *pb.ProgressBar {
  tmpl := `{{counters .}} {{bar . "[" "=" ">" "-" "]"}} {{speed .}} {{percent . | green}} {{rtime .}}`
  return pb.New64(size).
    Set(pb.Bytes, true).
    SetMaxWidth(1000).
    SetTemplate(pb.ProgressBarTemplate(tmpl))
}

func (downloader *Downloader) Download(sourceVUrl string, Parts []*bilibili.Part) error {
  var size int64 = 0
  for _, i := range Parts {
    size += i.Size
  }
  title := downloader.Title
  stream := Parts[0]
  mergedfilePath := "./" + title + "." + stream.Ext
  _, fileExists, _ := FileSize(mergedfilePath)
  if fileExists {
    fmt.Printf("%s: file already exists, skipping\n", mergedfilePath)
    return nil
  }
  downloader.bar = progressBar(size)
  downloader.bar.Start()
  paths := make([]string, len(Parts))
  for index, part := range Parts {
    partfileName := fmt.Sprintf("./%s[%d].%s", title, index, part.Ext)
    paths[index] = partfileName
    err := downloader.save(sourceVUrl, Parts[index], partfileName)
    if err != nil {
      return err
    }
  }
  downloader.bar.Finish()
  // TODO: need to implement this function
  return utils.MergeToMP4(paths, mergedfilePath, title)
}

func (downloader *Downloader) save(sourceVUrl string, Part *bilibili.Part, partfileName string) error {
  partSize, exists, _ := FileSize(partfileName)
  if exists && partSize == Part.Size {
    downloader.bar.Add64(Part.Size)
    return nil
  }
  tempFileName := partfileName + ".download"
  tempFileSize, _, err := FileSize(tempFileName)
  if err != nil {
    return err
  }
  headers := map[string]string{
    "Referer": sourceVUrl,
  }
  var (
    file *os.File
    fileError error
  )
  if tempFileSize > 0 {
    headers["Range"] = fmt.Sprintf("bytes=%d-", tempFileSize)  // TODO
    file, fileError = os.OpenFile(tempFileName, os.O_APPEND|os.O_WRONLY, 0644)
    downloader.bar.Add64(tempFileSize)
  } else {
    file, fileError = os.Create(tempFileName)
  }
  if fileError != nil {
    return fileError
  }

  // TODO: close and rename temp file at the end of this function
  defer func() {
    file.Close() // nolint
    if err == nil {
      os.Rename(tempFileName, partfileName) // nolint
    }
  }()

  temp := tempFileSize
  // TODO: must to know what this do
  for i := 0; ; i++ {
    written, err := downloader.writeFile(Part.URL, file, headers)
    if err == nil {
      break
    } else if i + 1 >= 10 {  // downloader.option.RetryTimes {
      return err
    }
    temp += written
    headers["Range"] = fmt.Sprintf("bytes=%d-", temp)
    time.Sleep(1 * time.Second)
  }

  return nil
}

func (downloader *Downloader) writeFile(url string, file *os.File, headers map[string]string) (int64, error) {
  res, err := request.Request(url, headers)
  if err != nil {
    return 0, err
  }
  defer res.Body.Close()

  barWriter := downloader.bar.NewProxyWriter(file)

  written, copyErr := io.Copy(barWriter, res.Body)
  if copyErr != nil && copyErr != io.EOF {
    return written, fmt.Errorf("file copy error: %s", copyErr)
  }
  return written, nil
}

// Get file size
func FileSize(filePath string) (int64, bool, error) {
  file, err := os.Stat(filePath)
  if err != nil {
    if os.IsNotExist(err) {
      return 0, false, nil
    }
    return 0, false, err
  }
  return file.Size(), true, nil
}
