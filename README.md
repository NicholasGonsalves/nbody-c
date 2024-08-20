Simple N-Body simulation in C.

# Setup on mac below:

`brew install glfw`
`brew install glew`

```
gcc -o opengl_project nbody.c \
    -I/opt/homebrew/Cellar/glew/2.2.0_1/include \
    -I/opt/homebrew/Cellar/glfw/3.4/include \
    -L/opt/homebrew/Cellar/glew/2.2.0_1/lib \
    -L/opt/homebrew/Cellar/glfw/3.4/lib \
    -lglfw -lGLEW -framework OpenGL
```

`./opengl_project`


https://github.com/user-attachments/assets/e9ae6fed-c8c4-4f8a-82b4-8c352c427647

