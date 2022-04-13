package request

import (
  "net/http"
  "errors"
  "io/ioutil"
  "fmt"
  "strconv"
  "time"
  "crypto/tls"
)

var FakeHeaders = map[string]string{
  "Accept":          "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8",
  "Accept-Charset":  "UTF-8,*;q=0.5",
  "Accept-Encoding": "gzip,deflate,sdch",
  "Accept-Language": "en-US,en;q=0.8",
  "User-Agent":      "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_13_6) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/69.0.3497.81 Safari/537.36",
}

func Get(url string) (string, error) {
  resp, err := http.Get(url)
  if err != nil {
    return "", errors.New("http get failed.")
  }
  defer resp.Body.Close()
  body, err := ioutil.ReadAll(resp.Body)
  if err != nil {
    return "", errors.New(fmt.Sprintf("%v", err))
  }
  // fmt.Println(string(body))
  return string(body), nil
}

func Request(url string, headers map[string]string) (*http.Response, error) {
  transport := &http.Transport{
    Proxy:               http.ProxyFromEnvironment,
    DisableCompression:  true,
    TLSHandshakeTimeout: 10 * time.Second,
    TLSClientConfig:     &tls.Config{InsecureSkipVerify: true},
  }
  client := &http.Client{
    Transport: transport,
    Timeout:   15 * time.Minute,
  }

  req, err := http.NewRequest(http.MethodGet, url, nil)
  if err != nil {
    return nil, err
  }
  for k, v := range FakeHeaders {
    req.Header.Set(k, v)
  }
  for k, v := range headers {
    req.Header.Set(k, v)
  }
  if _, ok := headers["Referer"]; !ok {
    req.Header.Set("Referer", url)
  }
  var (
    res          *http.Response
    requestError error
  )
  for i := 0; ; i++ {
    res, requestError = client.Do(req)
    if requestError == nil && res.StatusCode < 400 {
      break
    }
  }
  return res, nil
}

func Size(url string, refer string) int64 {
  headers := map[string]string{
    "Referer": refer,
  }
  res, _ := Request(url, headers)
  size, _ :=  strconv.ParseInt(res.Header.Get("Content-Length"), 10, 64)
  return size
}
