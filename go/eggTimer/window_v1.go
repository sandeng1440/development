package main

import (
	"fmt"
	"image"
	"image/color"
	"log"
	"math"
	"os"
	"strconv"
	"strings"
	"time"

	"gioui.org/app"
	"gioui.org/f32"
	"gioui.org/layout"
	"gioui.org/op"
	"gioui.org/op/clip"
	"gioui.org/op/paint"
	"gioui.org/text"
	"gioui.org/unit"
	"gioui.org/widget"
	"gioui.org/widget/material"
)

var progress float32
var progressIncrement chan float32

func main() {
	progressIncrement = make(chan float32)
	go func() {
		for {
			time.Sleep(time.Second / 25)
			progressIncrement <- 0.004
		}
	}()
	go func() {
		// create new window
		w := new(app.Window)
		w.Option(app.Title("Egg timer"))
		w.Option(app.Size(unit.Dp(400), unit.Dp(600)))
		if err := draw(w); err != nil {
			log.Fatal(err)
		}
		os.Exit(0)
	}()
	app.Main()
}

var margins = layout.Inset{
	Top:    unit.Dp(25),
	Bottom: unit.Dp(25),
	Right:  unit.Dp(35),
	Left:   unit.Dp(35),
}

func draw(w *app.Window) error {
	// ops are the operations from the UI
	var ops op.Ops

	// startButton is a clickable widget
	var startButton widget.Clickable

	// th defines the material design style
	th := material.NewTheme()

	// boilDurationInput is a textfield to input boil duration
	var boilDurationInput widget.Editor

	// is the egg boiling?
	var boiling bool
	var boilDuration float32

	go func() {
		for range progressIncrement {
			if boiling && progress < 1 {
				boilRemain := (1 - progress) * boilDuration
				// Format to 1 decimal.
				inputStr := fmt.Sprintf("%.1f", math.Round(float64(boilRemain)*10)/10)
				// Update the text in the inputbox
				boilDurationInput.SetText(inputStr)

				progress += 1.0 / 25.0 / boilDuration
				if progress >= 1 {
					progress = 1
				}

				w.Invalidate()
			}
		}
	}()

	// listen for events in the window.
	for {
		// detect what type of event
		switch e := w.Event().(type) {

		// this is sent when the application should re-render.
		case app.FrameEvent:
			gtx := app.NewContext(&ops, e)

			if startButton.Clicked(gtx) {
				boiling = !boiling

				if progress >= 1 {
					progress = 0
				}

				inputStr := boilDurationInput.Text()
				inputStr = strings.TrimSpace(inputStr)
				inputFloat, _ := strconv.ParseFloat(inputStr, 32)
				boilDuration = float32(inputFloat)
				boilDuration = boilDuration / (1 - progress)
			}

			// Let's try out the flexbox layout:
			layout.Flex{
				// Vertical alignment, from top to bottom
				Axis: layout.Vertical,
				// Empty space is left at the start, i.e. at the top
				Spacing: layout.SpaceStart,
			}.Layout(gtx,

				// egg
				layout.Rigid(
					func(gtx layout.Context) layout.Dimensions {
						// Draw a custom path, shaped like an egg
						var eggPath clip.Path

						op.Offset(image.Pt(gtx.Dp(200), gtx.Dp(125))).Add(gtx.Ops)
						eggPath.Begin(gtx.Ops)
						// Rotate from 0 to 360 degrees
						for deg := 0.0; deg <= 360; deg++ {

							// Egg math (really) at this brilliant site. Thanks!
							// https://observablehq.com/@toja/egg-curve
							// Convert degrees to radians
							// rad := deg / 360 * 2 * math.Pi
							rad := deg / 180 * math.Pi
							// Trig gives the distance in X and Y direction
							cosT := math.Cos(rad)
							sinT := math.Sin(rad)
							// Constants to define the eggshape
							a := 110.0
							b := 150.0
							d := 20.0
							// The x/y coordinates
							x := a * cosT
							y := -(math.Sqrt(b*b-d*d*cosT*cosT) + d*sinT) * sinT
							// Finally the point on the outline
							p := f32.Pt(float32(x), float32(y))
							// Draw the line to this point
							eggPath.LineTo(p)
						}
						// Close the path
						eggPath.Close()

						// Get hold of the actual clip
						eggArea := clip.Outline{Path: eggPath.End()}.Op()

						// Fill the shape
						// color := color.NRGBA{R: 255, G: 239, B: 174, A: 255}
						color := color.NRGBA{R: 255, G: uint8(239 * (1 - progress)), B: uint8(174 * (1 - progress)), A: 255}
						paint.FillShape(gtx.Ops, color, eggArea)

						d := image.Point{Y: 375}
						return layout.Dimensions{Size: d}
					},
				),

				// input field
				layout.Rigid(
					func(gtx layout.Context) layout.Dimensions {
						// margins
						m := layout.Inset{
							Top:    unit.Dp(0),
							Right:  unit.Dp(170),
							Bottom: unit.Dp(40),
							Left:   unit.Dp(170),
						}
						// ... and borders ...
						border := widget.Border{
							Color:        color.NRGBA{R: 204, G: 204, B: 204, A: 255},
							CornerRadius: unit.Dp(3),
							Width:        unit.Dp(2),
						}
						boilDurationInput.SingleLine = true
						boilDurationInput.Alignment = text.Middle
						ed := material.Editor(th, &boilDurationInput, "sec")
						return m.Layout(gtx,
							func(gtx layout.Context) layout.Dimensions {
								return border.Layout(gtx, ed.Layout)
							},
						)
					},
				),

				// progress bar
				layout.Rigid(
					func(gtx layout.Context) layout.Dimensions {
						return margins.Layout(gtx,
							func(gtx layout.Context) layout.Dimensions {
								progBar := material.ProgressBar(th, progress)
								return progBar.Layout(gtx)
							},
						)
					},
				),

				// button
				// We insert two rigid elements:
				// First one to hold a button ...
				layout.Rigid(
					func(gtx layout.Context) layout.Dimensions {
						return margins.Layout(gtx,
							func(gtx layout.Context) layout.Dimensions {
								text := "Start"
								if boiling && progress < 1 {
									text = "Stop"
								} else if boiling && progress >= 1 {
									text = "Finished"
								}
								btn := material.Button(th, &startButton, text)
								return btn.Layout(gtx)
							},
						)
					},
				),

				// spacer
				// ... then one to hold an empty spacer
				layout.Rigid(
					// The height of the spacer is 25 Device independent pixels
					layout.Spacer{Height: unit.Dp(25)}.Layout,
				),
			)
			e.Frame(gtx.Ops)

		// this is sent when the application is closed
		case app.DestroyEvent:
			return e.Err
		}
	}
}
