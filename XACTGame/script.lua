MainMenuOption = {
    title = "Options",
    x = 250,
    y = 300,
	width = 250,
	height = 300,
	TopLeftClr={
	  r=192,
	  g = 192,
	  b = 192,
	  a = 206
	},
	TopRightClr={
	  r = 192,
	  g = 192,
	  b = 192,
	  a = 192
	},
	BottomLeftClr={
	  r = 192,
	  g = 192,
	  b = 192,
	  a = 192
	},
	BottomRightClr={
	  r = 192,
	  g = 192,
	  b = 192,
	  a = 179
	}

}

InputMenuOption = {
    title = "Input Options",
    x = 250,
    y = 300,
	width = 250,
	height = 300,
	TopLeftClr={
	  r=0,
	  g = 98,
	  b = 138,
	  a = 206
	},
	TopRightClr={
	  r = 255,
	  g = 54,
	  b = 105,
	  a = 192
	},
	BottomLeftClr={
	  r = 200,
	  g = 100,
	  b = 105,
	  a = 192
	},
	BottomRightClr={
	  r = 0,
	  g = 10,
	  b = 73,
	  a = 179
	}

}

AudioMenuOption = {
    title = "AUDIO Options",
    x = 250,
    y = 300,
	width = 250,
	height = 300,
	TopLeftClr={
	  r=200,
	  g = 98,
	  b = 138,
	  a = 206
	},
	TopRightClr={
	  r = 255,
	  g = 54,
	  b = 105,
	  a = 192
	},
	BottomLeftClr={
	  r = 200,
	  g = 100,
	  b = 105,
	  a = 192
	},
	BottomRightClr={
	  r = 0,
	  g = 10,
	  b = 73,
	  a = 179
	}

}
VideoMenuOption = {
    title = "Input Options",
    x = 250,
    y = 300,
	width = 250,
	height = 300,
	TopLeftClr={
	  r=200,
	  g = 98,
	  b = 138,
	  a = 206
	},
	TopRightClr={
	  r = 255,
	  g = 54,
	  b = 105,
	  a = 192
	},
	BottomLeftClr={
	  r = 200,
	  g = 100,
	  b = 105,
	  a = 192
	},
	BottomRightClr={
	  r = 0,
	  g = 10,
	  b = 73,
	  a = 179
	}

}

output = function(a,b)
    printMessage("You can still call C++ functions from Lua functions!")
    return a + b
end