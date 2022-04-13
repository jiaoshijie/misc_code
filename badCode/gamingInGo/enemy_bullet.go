package main

import (
	"github.com/veandco/go-sdl2/sdl"
)

type Enemy_Bullet struct {
  tex *sdl.Texture
  x, y float64
  is_active bool
}

const (
  enemy_bulletSize = 32
  enemy_bulletSpeed = 0.5
)

func newEnemyBullet(renderer *sdl.Renderer, x, y float64) (e_bl Enemy_Bullet) {
  e_bl.tex = TextureFromFile(renderer, "./scriptes/enemy_bullet.bmp")
  e_bl.x = x
  e_bl.y = y
  e_bl.is_active = true
  return e_bl
}

func (e_bl *Enemy_Bullet) draw(renderer *sdl.Renderer) {
  renderer.Copy(
    e_bl.tex,
    &sdl.Rect{ X: 0, Y: 0, W: enemy_bulletSize, H: enemy_bulletSize },
    &sdl.Rect{ X: int32(e_bl.x), Y: int32(e_bl.y), W: enemy_bulletSize, H: enemy_bulletSize })
  e_bl.y += enemy_bulletSpeed
  if e_bl.y > screenHeight {
    e_bl.is_active = false
  }
}

func (e_bl *Enemy_Bullet) kill_player(p Player) (bool) {
  if e_bl.x > p.x && e_bl.y > p.y && e_bl.x < p.x + playerSize - 12 && e_bl.y < p.y + playerSize - 12 {
    return true
  }
  return false
}
