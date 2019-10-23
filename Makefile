CC = g++
CFLAGS = -Wall
PROG = particles

SRCS = main.cpp floor.cpp hole.cpp particle.cpp scene.cpp bmpload.cpp vertex.cpp canon.cpp camera.cpp sceneobject.cpp lightbulb.cpp
ifeq ($(shell uname),Darwin)
	LIBS = -framework OpenGL -framework GLUT
else
	LIBS = -lglut -lGLU -lopengl
endif

all: $(PROG)

$(PROG):	$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)

clean:
	rm -f $(PROG)
