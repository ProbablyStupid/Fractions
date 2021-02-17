#pragma once

#include "FractionsFiles.h"

#define GLEW_STATIC

#include <GL/glew.h>
#include <glm/glm/glm.hpp>

void FractionsCallback();

typedef struct FractionsContext
{
} FractionsContext;

void FractionsCreateContext(FractionsContext*);
void setCurrentFractionsContext(FractionsContext*);

void configureWindow(const char*, unsigned int, unsigned int);
void createWindow();
void hideWindow();
void showWindow();
[[depreceated]] void destroyWindow();

void makeEngineWindow();

typedef struct VAO
{
	unsigned long long int id;
} VAO;

void createVAO(VAO*);

/* only used when modifying the way the renderer works -> should happen automatically */
void useVAO(VAO*);
void flushVAO();
//

typedef struct VertexBufferConfiguration
{
	float* data;
	// TODO
	GLenum usage;
	unsigned long long int size;
} VertexBufferConfiguration;

typedef struct VertexBuffer
{
	/* Contains the data */
	VertexBufferConfiguration configuration;

	unsigned long long int id;
} VertexBuffer;

void createVertexBuffer(VertexBuffer*);
void assignVertexBufferVAO(VAO*);
void flushVertexBuffer(VertexBuffer*);
/* Renderer Access */
void selectVertexBuffer(VertexBuffer*);