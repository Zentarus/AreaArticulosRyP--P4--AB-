# Nombre del programa
PROGRAMA = buscaRyP

# Compilador y flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

# Directorios de inclusión
INC_DIR = librerias
INC_FLAGS = -I$(INC_DIR)

# Archivos fuente y objetos
SRCS = buscaRyP.cc
OBJS = $(SRCS:.cc=.o)

# Dependencias
DEPS = $(INC_DIR)/arbol.hh $(INC_DIR)/articulo.hh $(INC_DIR)/pagina.hh

# Reglas de compilación
$(PROGRAMA): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(PROGRAMA)

# Reglas de compilación de objetos
%.o: %.cc $(DEPS)
	$(CXX) $(CXXFLAGS) $(INC_FLAGS) -c $< -o $@

# Limpieza de archivos generados
clean:
	rm -f $(OBJS) $(PROGRAMA)
