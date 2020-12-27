#include "Shader.h"
using namespace std;

// Constructeur
// Nous permet de créer un shader à la volée pour nos objets
Shader::Shader( const GLchar *vertexPath, const GLchar *fragmentPath ){
    // 1. Retrieve the vertex/fragment source code from filePath
    string vertexCode;
    string fragmentCode;
    ifstream vShaderFile;
    ifstream fShaderFile;
    // ensures ifstream objects can throw exceptions:
    vShaderFile.exceptions (ifstream::badbit );
    fShaderFile.exceptions (ifstream::badbit );
    try{
        // Open files
        vShaderFile.open( vertexPath );
        fShaderFile.open( fragmentPath );
        stringstream vShaderStream, fShaderStream;
        // Read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf( );
        fShaderStream << fShaderFile.rdbuf( );
        // close file handlers
        vShaderFile.close( );
        fShaderFile.close( );
        // Convert stream into string
        vertexCode = vShaderStream.str( );
        fragmentCode = fShaderStream.str( );
    }
    catch ( ifstream::failure e )
    {
        cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << endl;
    }
    
    const GLchar *vShaderCode = vertexCode.c_str( );
    const GLchar *fShaderCode = fragmentCode.c_str( );
    // 2. Compile shaders
    GLuint vertex, fragment;
    GLint success;
    GLchar infoLog[512];
    // Vertex Shader
    vertex = glCreateShader( GL_VERTEX_SHADER );
    glShaderSource( vertex, 1, &vShaderCode, NULL );
    glCompileShader( vertex );
    // Print compile errors if any
    glGetShaderiv( vertex, GL_COMPILE_STATUS, &success );
    if ( !success )
    {
        glGetShaderInfoLog( vertex, 512, NULL, infoLog );
        cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
    }
    // Fragment Shader
    fragment = glCreateShader( GL_FRAGMENT_SHADER );
    glShaderSource( fragment, 1, &fShaderCode, NULL );
    glCompileShader( fragment );
    // Print compile errors if any
    glGetShaderiv( fragment, GL_COMPILE_STATUS, &success );
    if ( !success )
    {
        glGetShaderInfoLog( fragment, 512, NULL, infoLog );
        cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
    }
    // Shader Program
    this->Program = glCreateProgram( );
    glAttachShader( this->Program, vertex );
    glAttachShader( this->Program, fragment );
    glLinkProgram( this->Program );
    // Print linking errors if any
    glGetProgramiv( this->Program, GL_LINK_STATUS, &success );
    if (!success)
    {
        glGetProgramInfoLog( this->Program, 512, NULL, infoLog );
        cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
    }
    // Delete the shaders as they're linked into our program now and no longer necessery
    glDeleteShader( vertex );
    glDeleteShader( fragment );
    
}
// Uses the current shader
void Shader::Use(){
    glUseProgram(this->Program);
}