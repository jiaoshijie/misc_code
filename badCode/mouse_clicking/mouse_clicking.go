package main

import (
  "fmt"
  "os"
  "strconv"
  "time"

  "github.com/go-vgo/robotgo"
)

type point [2]int

var (
  run            = false
  mousePointList []point
)

func main() {
  if len(os.Args) == 1 { // 单点 0.5秒
    oneClicked()
    return
  }

  // 多点 第二个参数 次数
  times, err := strconv.Atoi(os.Args[1])
  if times < 1 || err != nil {
    fmt.Printf("Error [%s] [获取鼠标点击数] \n", os.Args[0])
    return
  }
  fmt.Printf("\n\t获取鼠标点击数：%d\n", times)
  for i := 0; i < times; i++ {
    fmt.Printf("\t请把鼠标移动到指定地方，按下 F4\n")
    if robotgo.AddEvent("f4") {
      x, y := robotgo.GetMousePos()
      fmt.Printf("第%v次 记录 x=%v y=%v\n", i+1, x, y)
      mousePointList = append(mousePointList, point{x, y})
      time.Sleep(time.Second)
    } else {
      i--
    }
  }
  fmt.Println(mousePointList)

  go switchRun()
  fmt.Println("请按键盘 F4 开启或停止")
  for ; ; time.Sleep(time.Second / 2) {
    if run {
      for i := 0; i < len(mousePointList); i++ {
        robotgo.MoveClick(mousePointList[i][0], mousePointList[i][1], "left", true)
      }
    }
  }

}

func oneClicked() {
  go switchRun()
  fmt.Println("请按键盘 F4 开启或停止")
  for ; ; time.Sleep(time.Second / 4) {
    if run {
      robotgo.MouseClick("left", true)
    }
  }
}

func switchRun() {
  for ; ; time.Sleep(time.Second / 2) {
    if robotgo.AddEvent("f4") {
      if run {
        fmt.Println("停止")
      } else {
        fmt.Println("开始")
      }
      run = !run
    }
  }
}
