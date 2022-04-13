package utils

import (
  "fmt"
  "bytes"
  "os"
  "os/exec"
  "regexp"
)

func runMergeCmd(cmd *exec.Cmd, paths []string, mergeFilePath string) error {
  var stderr bytes.Buffer
  cmd.Stderr = &stderr
  err := cmd.Run()
  if err != nil {
    return fmt.Errorf("%s\n%s", err, stderr.String())
  }

  if mergeFilePath != "" {
    os.Remove(mergeFilePath) // nolint
  }
  // remove parts
  for _, path := range paths {
    os.Remove(path) // nolint
  }
  return nil
}

func MatchOneOf(text string, patterns ...string) []string {
  var (
    re    *regexp.Regexp
    value []string
  )
  for _, pattern := range patterns {
    re = regexp.MustCompile(pattern)
    value = re.FindStringSubmatch(text)
    if len(value) > 0 {
      return value
    }
  }
  return nil
}

func MergeToMP4(paths []string, mergedfilePath string, title string) error {
  mergeFilePath := title + ".txt" // merge list file should be in the current directory

  // write ffmpeg input file list
  mergeFile, _ := os.Create(mergeFilePath)
  for _, path := range paths {
    mergeFile.Write([]byte(fmt.Sprintf("file '%s'\n", path))) // nolint
  }
  mergeFile.Close() // nolint

  cmd := exec.Command(
    "ffmpeg", "-y", "-f", "concat", "-safe", "0",
    "-i", mergeFilePath, "-c", "copy", "-bsf:a", "aac_adtstoasc", mergedfilePath,
  )
  return runMergeCmd(cmd, paths, mergeFilePath)
}
