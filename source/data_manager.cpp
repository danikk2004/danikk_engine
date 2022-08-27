
#define STB_IMAGE_IMPLEMENTATION 1
#define STBI_ONLY_PNG 1
#include <glad/glad.h>
#include <stb_image.h>
#include <zip.h>

#include <danikk_framework/memory_stream.h>
#include <danikk_framework/file_stream.h>
#include <danikk_framework/path_buffer.h>
#include <danikk_framework/string_buffer.h>
#include <danikk_framework/zip.h>
#include <danikk_framework/cataloged_map.h>
#include <danikk_framework/memory.h>
#include <danikk_framework/cout_features.h>
#include <danikk_framework/format.h>

#include <danikk_engine/data_manager.h>
#include <danikk_engine/shader.h>
#include <danikk_engine/texture.h>
#include <danikk_engine/localization.h>

#include <danikk_engine/internal/gl_memory_manager.h>
#include <danikk_engine/internal/asset.h>

using namespace danikk_framework;

namespace danikk_engine
{
	using namespace danikk_framework;
	using namespace internal;

    zip_t* data_archive = NULL;

    constexpr size_t GL_LOG_SIZE = 256;

    MemoryStream dataBuffer;
    String shaderFormatBuffer;

    CatalogedMap<AssetContainer*> assets;

    static bool loadDataToBuffer(const char* name, const char* extension)
    {
        StringBuffer<256> zip_path_buffer;
        zip_path_buffer << name << "." << extension;
        const char* zip_path = zip_path_buffer.c_string();
        
        zip_stat_t data_stat;

        zip_stat_init(&data_stat);

        int error = zip_stat(data_archive, zip_path, 0, &data_stat);

        if(error)
        {
        	danikk_framework::formatWrite(cerr, "% % % %\n",
        			(String&)localization("error/cant_load_asset1"),
					name,
					(String&)localization("error/cant_load_asset2"),
					zip_error_code_tostr(error));
            return false;
        }

        zip_file* data_zip_file = zip_fopen(data_archive, zip_path_buffer.c_string() , ZIP_RDONLY);

        size_t data_size = data_stat.size;

        dataBuffer.resize(data_size);

        zip_fread(data_zip_file, dataBuffer.data(), data_size);
        zip_fclose(data_zip_file);
        return true;
    }

    namespace internal
	{
		void initDataManager()
		{
			PathBuffer CurrentPathBuffer;
			CurrentPathBuffer
				.getExecutableDirectory()
				.setFileName("data.zip");

			int error;

			data_archive = zip_open(CurrentPathBuffer.c_string(), ZIP_RDONLY, &error);

			if(!error)
			{
				return;
			}

			//В случае ошибки нужно будет искать файл в более верхних директориях.
			//Это нужно для отладки что-бы не дублировать data файл.
			if(strstartswith(CurrentPathBuffer.getLastDirectoryName(),"build"))
			{

				CurrentPathBuffer
					.popDirectory()
					.setFileName("data.zip");

				data_archive = zip_open(CurrentPathBuffer.c_string(), ZIP_RDONLY, &error);
				return;
			}
			CurrentPathBuffer.popDirectory();
			if(strstartswith(CurrentPathBuffer.getLastDirectoryName(),"build"))
			{

				CurrentPathBuffer
					.popDirectory()
					.setFileName("data.zip");

				data_archive = zip_open(CurrentPathBuffer.c_string(), ZIP_RDONLY, &error);
				return;
			}

			StringBuffer<512> error_buffer;
			error_buffer
			<< localization("error/cant_open_data_file")
			<< zip_error_code_tostr(error);
			fatalError(error_buffer.c_string());
		}

	    static void freeTexture(AssetContainer& container)
	    {
	    	glDeletetexture(container.texture_data.handle);
	    }

		static void freeShader(AssetContainer& container)
	    {
	    	glDeleteShader(container.shader_data.handle);
	    }

		static void freeModel(AssetContainer& container)
	    {
			(void)container;
	    	cout << "Имплементировать!!!" << endl;
	    	cout << __FILE__ << " " << __LINE__ << endl;
	    	abort();
	    }

		asset_free_func_t asset_free_funcs[3]
		{
			freeTexture,
			freeShader,
			freeModel,
		};
	}

    static uint compileShader(const char* shader_name, const char* code, size_t type)
    {
    	uint shader;

        glexec
		(
			shader = glCreateShader(type);
            glShaderSource(shader, 1, (const GLchar* const*)&code, NULL);
            glCompileShader(shader);

            int success;
            char infoLog[GL_LOG_SIZE];

            glGetProgramiv(shader, GL_COMPILE_STATUS, &success);
            if (success)
            {
                glGetProgramInfoLog(shader, GL_LOG_SIZE, NULL, infoLog);
                cerr << "[danikk_framework::compileShader]" << localization("error/shader_compile") << shader_name << endl;
                cerr << infoLog << endl;
            }
		)

    	return shader;
    }

    Shader loadShader(const char* name)
    {
    	AssetContainer*& container = assets.get(name);

    	if(isNullRef(container))
    	{
        	int vertexShader;
        	int fragmentShader;
        	int program;

            loadDataToBuffer(name, "vert");
            vertexShader = compileShader(name, dataBuffer.c_string(), GL_VERTEX_SHADER);
    		loadDataToBuffer(name, "frag");
    		fragmentShader = compileShader(name, dataBuffer.c_string(), GL_FRAGMENT_SHADER);

            glexec
        	(
                program = glCreateProgram();
                glAttachShader(program, vertexShader);
                glAttachShader(program, fragmentShader);
                glLinkProgram(program);

                int success;
                char infoLog[GL_LOG_SIZE];

                glGetProgramiv(program, GL_LINK_STATUS, &success);
                if (!success)
                {
                    glGetProgramInfoLog(program, GL_LOG_SIZE, NULL, infoLog);
                    cerr << "[danikk_engine::compileShader] cant compile shader " << name << endl;
                    cerr << infoLog << endl;
                }

            	glDetachShader(program, vertexShader);
            	glDetachShader(program, fragmentShader);
                glDeleteShader(vertexShader);
                glDeleteShader(fragmentShader);
            )

    		AssetContainer* newContainer = structmalloc<AssetContainer>();
            newContainer->type = texture_enum;
            newContainer->ref_count = 0;
            newContainer->shader_data.handle = program;
            newContainer->ref_count++;
        	assets.insert(name, newContainer);
        	return Shader(*newContainer);
    	}
    	else
    	{
        	container->ref_count++;
        	return Shader(*container);
    	}
    }

    Texture loadTexture(const char* name)
    {
    	AssetContainer*& container = assets.get(name);

    	if(isNullRef(container))
    	{
    		int width;
    		int height;
            int channels;
            uint texture_handle;
            char* data;

            loadDataToBuffer(name, "png");
            data = (char*)stbi_load_from_memory((stbi_uc*)dataBuffer.data(), dataBuffer.size(), &width, &height, &channels, 0);

            glexec
    		(
    			texture_handle = glGenTexture();
    			glBindTexture(GL_TEXTURE_2D, texture_handle);
    			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,  GL_MIRRORED_REPEAT);
    			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,  GL_MIRRORED_REPEAT);
    			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    		)
            free(data);

            AssetContainer* newContainer = structmalloc<AssetContainer>();
            newContainer->type = texture_enum;
            newContainer->ref_count = 0;
            newContainer->texture_data.handle = texture_handle;
            assets.insert(name, newContainer);
        	return Texture(*newContainer);
    	}
    	else
    	{
        	return Texture(*container);
    	}
    }
}
