package main

import (
  // "fmt"
  "github.com/veandco/go-sdl2/sdl"
)

type Player struct {
  tex *sdl.Texture
  x, y float64
  bullets [30]Bullet
}

const (
  playerSpeed = 15
  playerSize = 105
)

func newPlayer(renderer *sdl.Renderer) (p Player) {
  p.x = screenWidth / 2.0 - playerSize / 2.0
  p.y = screenHeight - playerSize
  // p.bullets = nil
  p.tex = TextureFromFile(renderer, "./scriptes/player.bmp")
  // defer p.tex.Destroy()

  return p
}

func (p *Player) draw(renderer *sdl.Renderer, e []basicEnemy) {
  renderer.Copy(
    p.tex,
    &sdl.Rect{ X: 0, Y: 0, W: playerSize, H: playerSize },
    &sdl.Rect{ X: int32(p.x), Y: int32(p.y), W: playerSize, H: playerSize })
  // for _, bl := range(p.bullets) {  // just use it when not modify
  //   bl.draw(renderer)
  // }
  for i := 0; i < len(p.bullets); i++ {
    if p.bullets[i].is_active {
      p.bullets[i].draw(renderer)
      p.bullets[i].kill_enemy(e)
    }
  }
}

func (p *Player) update(renderer *sdl.Renderer) {
  keys := sdl.GetKeyboardState()
  if keys[sdl.SCANCODE_A] == 1 {
    // left
    if p.x > -50 { p.x -= playerSpeed }
  } else if keys[sdl.SCANCODE_D] == 1 {
    // right
    if p.x < 550 { p.x += playerSpeed }
  } else if keys[sdl.SCANCODE_W] == 1 {
    if p.y > screenHeight / 2.0 - 105 { p.y -= playerSpeed }
  } else if keys[sdl.SCANCODE_S] == 1 {
    if p.y < screenHeight - 105 { p.y += playerSpeed }
  }
  // NOTICE: this can move and shoot
  if keys[sdl.SCANCODE_SPACE] == 1 {
    p.fire(renderer)
  }
}

func (p *Player) fire(renderer *sdl.Renderer) {
  var i int = 0
  one := true
  for i = 0; i < len(p.bullets); i++ {
    if p.bullets[i].is_active == false {
      if one {
        p.bullets[i] = newBullet(renderer, p.x + playerSize / 2.0 + 5, p.y + 5)
        one = false
      } else {
        p.bullets[i] = newBullet(renderer, p.x + 15, p.y + 5)
        return
      }
    }
  }
}
