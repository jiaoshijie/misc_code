package main

import (
  // "fmt"
  "github.com/veandco/go-sdl2/sdl"
)

type Bullet struct {
  tex *sdl.Texture
  x, y float64
  is_active bool
}

const (
  bulletSize = 32
  bulletSpeed = 1
)

func newBullet(renderer *sdl.Renderer, x, y float64) (bl Bullet) {
  bl.tex = TextureFromFile(renderer, "./scriptes/player_bullet.bmp")
  bl.x = x
  bl.y = y
  bl.is_active = true
  return bl
}

func (bl *Bullet) draw(renderer *sdl.Renderer) {
  renderer.Copy(
    bl.tex,
    &sdl.Rect{ X: 0, Y: 0, W: bulletSize, H: bulletSize },
    &sdl.Rect{ X: int32(bl.x), Y: int32(bl.y), W: bulletSize, H: bulletSize })
  bl.y -= bulletSpeed
  if bl.y < 0 {
    bl.is_active = false
  }
}

func (bl *Bullet) kill_enemy(e []basicEnemy) {
  for i := 0; i < len(e); i++ {
    if e[i].is_active == true {
      if bl.x > e[i].x && bl.y > e[i].y && bl.x < e[i].x + basicEnemySize - 1 && bl.y < e[i].y + basicEnemySize - 1 {
        bl.is_active = false
        e[i].is_active = false
      }
    }
  }
}
