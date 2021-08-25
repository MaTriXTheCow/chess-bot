package main

import (
	"bytes"
	"fmt"
	"log"
	"os/exec"
)

func main() {
	var out bytes.Buffer

	cmd := exec.Command(
		"cl",
    "/Fochessbot.obj",
		"/W4",
		"/EHsc",
		"window.cpp",
		"user32.lib",
    "Gdi32.lib",
		"/link",
		"/out:chessbot.exe",
		"/SUBSYSTEM:CONSOLE",
		"/ENTRY:wWinMainCRTStartup",
	)

	cmd.Stdin = nil
	cmd.Stdout = &out

	err := cmd.Run()

	if err != nil {
    fmt.Printf("%s", out.String())
		log.Fatal(err)
	}

	fmt.Printf("%s\n", out.String())
}
