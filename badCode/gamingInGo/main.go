package main

import (
  "fmt"
  "math/rand"
  "time"

  "github.com/veandco/go-sdl2/sdl"
)

const (
  screenWidth = 600
  screenHeight = 800
)

var running bool = true
var game_over int = 0
var box_message string

func TextureFromFile(renderer *sdl.Renderer, filename string) (tex *sdl.Texture) {
  img, err := sdl.LoadBMP(filename)
  if err != nil {
    panic(fmt.Errorf("load img %v failed, error = %v", filename, err))
  }
  defer img.Free()

  tex, err = renderer.CreateTextureFromSurface(img)
  if err != nil {
    panic(fmt.Errorf("create texture %v failed, error = %v", filename, err))
  }
  return tex
}


func main() {
  rand.Seed(time.Now().UnixNano())
  if err := sdl.Init(sdl.INIT_EVERYTHING); err != nil {
    // panic(err)
    fmt.Println("initializing SDL: ", err)
    return
  }

  // create a window
  window, err := sdl.CreateWindow(
    "Gaming in Go",
    sdl.WINDOWPOS_UNDEFINED, sdl.WINDOWPOS_UNDEFINED,
    screenWidth, screenHeight,
    sdl.WINDOW_OPENGL)

  if err != nil {
    fmt.Println("Create window: ", err)
    return
  }
  defer window.Destroy()

  // create a renderer
  renderer, err := sdl.CreateRenderer(window, -1, sdl.RENDERER_ACCELERATED)
  if err != nil {
    fmt.Println("Create renderer: ", err)
    return
  }
  defer renderer.Destroy()

  var con int32 = 0
  for con == 0 {
    game_play(renderer)
    if game_over == 0 {
      box_message = "Do you want to quit?"
    } else if game_over == 1 {
      box_message = "Congratulations, You win!!!\nDo you want to quit?"
    } else if game_over == 2 {
      box_message = "You failed!!!\nDo you want to quit?"
    }
    con = win_message_box(box_message)
    running = true
    game_over = 0
  }
}


func game_play(renderer *sdl.Renderer) {
  player := newPlayer(renderer)

  var enemies []basicEnemy

  for i := 0; i < 5; i++ {
    for j := 0; j < 3; j++ {
      x := float64(i) * screenWidth / 5.0
      y := float64(j) * basicEnemySize + 10
      enemy := newBasicEnemy(renderer, x, y)
      enemies = append(enemies, enemy)
    }
  }

  for running {  // Event loop
    for event := sdl.PollEvent(); event != nil; event = sdl.PollEvent() {
      switch event.GetType() {
      case sdl.QUIT:
        game_over = 0
        running = false
        break
      case sdl.KEYDOWN:
        player.update(renderer)
      default:
        // NOTICE: do nothing
      }
    }

    renderer.Clear()
    player.draw(renderer, enemies)
    for i := 0; i < len(enemies); i++ {
      if enemies[i].is_active == true {
        enemies[i].draw(renderer)
        if enemies[i].bullet.kill_player(player) {
          game_over = 2
          running = false
          break
        }
      }
    }
    renderer.Present()
    if is_win(enemies) {
      game_over = 1
      running = false
    }
  }
}

func is_win(es []basicEnemy) bool {
  for _, e := range(es) {
    if e.is_active == true {
      return false
    }
  }
  return true
}


func win_message_box(box_message string) int32 {
  buttons := []sdl.MessageBoxButtonData{
    { Flags: 0, ButtonID: 0, Text: "no" },
    { Flags: sdl.MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, ButtonID: 1, Text: "yes" },
  }
  var color [5]sdl.MessageBoxColor
  color[0] = sdl.MessageBoxColor{ R: 0, G: 0, B: 0 }  // background
  color[1] = sdl.MessageBoxColor{ R: 255, G: 255, B: 255 }  // text
  color[2] = sdl.MessageBoxColor{ R: 0, G: 0, B: 0 }  // button border
  color[3] = sdl.MessageBoxColor{ R: 126, G: 112, B: 112 }  // button background
  color[4] = sdl.MessageBoxColor{ R: 0, G: 0, B: 0 }  // button selected


  colorScheme := sdl.MessageBoxColorScheme{
    Colors: color,
  }

  // TODO: game failed message
  messageboxdata := sdl.MessageBoxData{
    Flags: sdl.MESSAGEBOX_INFORMATION,
    Window: nil,
    Title: "Game over",
    Message: box_message,
    Buttons: buttons,
    ColorScheme: &colorScheme,
  }

  var buttonid int32
  var err error
  if buttonid, err = sdl.ShowMessageBox(&messageboxdata); err != nil {
    fmt.Println("error displaying message box")
    return -1
  }
  return buttonid
}
