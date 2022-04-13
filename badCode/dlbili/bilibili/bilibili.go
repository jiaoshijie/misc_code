package bilibili

import (
  "fmt"
  "encoding/json"

  "github.com/jiaoshijie/dlbili/request"
  "github.com/jiaoshijie/dlbili/utils"
)

type EpInfo struct {
  Aid int `json:aid`
  BVid string `json:bvid`
  Cid int `json:cid`
}

type BilibiliData struct {
  EpInfo EpInfo `json:EpInfo`
  EpList []EpInfo `json:EpList`
}

type BilibiliOptions struct {
  url string
  html string
  bangumi bool
  aid int
  cid int
  bvid string
}

type dashStream struct {
  ID        int    `json:"id"`
  BaseURL   string `json:"baseUrl"`
  Bandwidth int    `json:"bandwidth"`
  MimeType  string `json:"mimeType"`
  Codecid   int    `json:"codecid"`
  Codecs    string `json:"codecs"`
}

type dashStreams struct {
  Video []dashStream `json:"video"`
  Audio []dashStream `json:"audio"`
}

type dashInfo struct {
  CurQuality  int         `json:"quality"`
  Description []string    `json:"accept_description"`
  Quality     []int       `json:"accept_quality"`
  Streams     dashStreams `json:"dash"`
}

type dash struct {
  Code    int      `json:"code"`
  Message string   `json:"message"`
  Data    dashInfo `json:"data"`
  Result  dashInfo `json:"result"`
}

type Part struct {
  URL  string `json:"url"`
  Size int64  `json:"size"`
  Ext  string `json:"ext"`
}

const (
  bilibiliAPI        = "https://api.bilibili.com/x/player/playurl?"
  bilibiliBangumiAPI = "https://api.bilibili.com/pgc/player/web/playurl?"
  bilibiliTokenAPI   = "https://api.bilibili.com/x/player/playurl/token?"
)

const referer = "https://www.bilibili.com"

func Extractor(url string) ([]*Part, error) {
  html, err := request.Get(url)
  if err != nil {
    return nil, err
  }
  dataString := utils.MatchOneOf(html, `window.__INITIAL_STATE__=(.+?);\(function`)[1]
  var data BilibiliData
  err = json.Unmarshal([]byte(dataString), &data)
  if err != nil {
    return nil, err
  }
  aid := data.EpInfo.Aid
  cid := data.EpInfo.Cid
  bvid := data.EpInfo.BVid
  if aid <= 0 || cid <= 0 || bvid == "" {
    aid = data.EpList[0].Aid
    cid = data.EpList[0].Cid
    bvid = data.EpList[0].BVid
  }
  options := BilibiliOptions{
    url:     url,
    html:    html,
    bangumi: true,
    aid:     aid,
    cid:     cid,
    bvid:    bvid,
  }
  return bilibiliDownload(options), nil
}

func bilibiliDownload(options BilibiliOptions) []*Part {
  // html = options.html
  api := genAPI(options.aid, options.cid, 64, options.bvid, options.bangumi)  // TODO: quality 80
  // fmt.Println(api)
  jsonString, _ := request.Get(api)
  var data dash
  json.Unmarshal([]byte(jsonString), &data)
  var dashData dashInfo
  if data.Data.Description == nil {
    dashData = data.Result
  } else {
    dashData = data.Data
  }

  var audioPart *Part
  if dashData.Streams.Audio != nil {
    var targetURL string
    bandwidth := 0
    for _, stream := range dashData.Streams.Audio {
      if stream.Bandwidth > bandwidth {
        bandwidth = stream.Bandwidth
        targetURL = stream.BaseURL
      }
    }
    s := request.Size(targetURL, referer)
    audioPart = &Part{
      URL: targetURL,
      Size: s,
      Ext: "m4a",
    }
  }
  var Parts = make([]*Part, 0, 2)
  if dashData.Streams.Video != nil {
    var targetURL string
    bandwidth := 0
    for _, stream := range dashData.Streams.Video {
      if stream.Bandwidth > bandwidth {
        bandwidth = stream.Bandwidth
        targetURL = stream.BaseURL
      }
    }
    s := request.Size(targetURL, referer)
    Parts = append(Parts, &Part{
      URL: targetURL,
      Size: s,
      Ext: "mp4",
    })
    if audioPart != nil {
      Parts = append(Parts, audioPart)
    }
  }
  return Parts
}

func genAPI(aid, cid, quality int, bvid string, bangumi bool) string {
  var (
    baseAPIURL string
    params string
  )
  var api string
  if bangumi {
    params = fmt.Sprintf(
      "cid=%d&bvid=%s&qn=%d&type=&otype=json&fourk=1&fnver=0&fnval=16",
      cid, bvid, quality,
    )
    baseAPIURL = bilibiliBangumiAPI
  }  // else
  api = baseAPIURL + params
  return api
}
