package main

import (
  "errors"
  "fmt"
  "os"
  "strings"

  // "encoding/json"

  "github.com/fatih/color"
  "github.com/urfave/cli/v2"

  "github.com/jiaoshijie/dlbili/bilibili"
  "github.com/jiaoshijie/dlbili/downloader"
)

func main() {
  cli.VersionPrinter = func(c *cli.Context) {
    blue := color.New(color.FgBlue)
    cyan := color.New(color.FgCyan)
    fmt.Fprintf(
      color.Output,
      "\n%s, version: %s.\n\n",
      blue.Sprintf("bilibili Download"),
      cyan.Sprintf("nightly"),
    )
  }
  app := &cli.App{
    Name: "bilibili download",
    Usage: "download bilibili Video",
    Version: "nightly version",
    Flags: []cli.Flag{
      &cli.BoolFlag{
        Name: "Info",
        Aliases: []string{"i"},
        Usage: "get vidoe info",
      },
      &cli.StringFlag{
        Name: "stream-format",
        Aliases: []string{"f"},
        Usage: "Select specific stream to download",
      },
    },
    Action: func(c *cli.Context) error {
      args := c.Args().Slice()
      if len(args) < 1 {
        return errors.New("too few arguments...")
      }
      // TODO:
      var isErr bool
      for _, videoURL := range args {
        if err := download(c, videoURL); err != nil {
          fmt.Fprintf(
            color.Output,
            "Downloading %s error: %s\n",
            color.CyanString("%s", videoURL),
            color.RedString("%v", err),
          )
          isErr = true
        }
      }
      if isErr {
        return cli.Exit("", 1)
      }
      return nil
    },
  }

  err := app.Run(os.Args)
  if err != nil {
    fmt.Fprintf(
      color.Output,
      "Run %s failed: %s\n",
      color.CyanString("%s", app.Name),
      color.RedString("%v", err),
    )
    os.Exit(1)
  }
}

func download(cli *cli.Context, videoURL string) error {
  // https://www.bilibili.com/bangumi/play/ep145976
  Extract(videoURL)
  return nil
}


func Extract(u string) (error) {
  u = strings.TrimSpace(u)  // 移除后面的空格等空白字符
  data, _ := bilibili.Extractor(u)
  dler := downloader.Downloader{Title: "dl_video"}
  dler.Download(u, data)
  return nil
}
