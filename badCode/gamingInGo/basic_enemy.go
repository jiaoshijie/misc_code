package main

import (
	"math/rand"

	"github.com/veandco/go-sdl2/sdl"
)

type basicEnemy struct {
  tex *sdl.Texture
  x, y float64
  is_active bool
  bullet Enemy_Bullet
}

const (
  basicEnemySize = 105
)

func newBasicEnemy(renderer *sdl.Renderer, x, y float64) (be basicEnemy) {
  // be.x = float64(rand.Intn(screenWidth - basicEnemySize))
  // rand.Seed(time.Now().UnixNano())
  // be.y = 5
  be.x = x
  be.y = y
  be.tex = TextureFromFile(renderer, "./scriptes/basic_enemy.bmp")
  be.is_active = true
  be.bullet = Enemy_Bullet{ nil, 0, 0, false }
  return be
}

func (be *basicEnemy) draw(renderer *sdl.Renderer) {
  renderer.CopyEx(
    be.tex,
    &sdl.Rect{ X: 0, Y: 0, W: basicEnemySize, H: basicEnemySize },
    &sdl.Rect{ X: int32(be.x), Y: int32(be.y), W: basicEnemySize, H: basicEnemySize }, 180,
    &sdl.Point{X: basicEnemySize / 2, Y: basicEnemySize / 2}, sdl.FLIP_NONE)

  if be.bullet.is_active == true {
    be.bullet.draw(renderer)
  } else {
    be.fire(renderer)
  }
}

func (be *basicEnemy) fire(renderer *sdl.Renderer) {
  if rand.Intn(10000) == 10 {  // fire
    be.bullet = newEnemyBullet(renderer, be.x + basicEnemySize / 2 - 15, be.y + basicEnemySize )
  }
}
