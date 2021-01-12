import os

shaders = [x for x in os.listdir() if 'glsl' in x and not 'glsl.h' in x]

for shader_path in shaders:
    with open(shader_path, 'r') as shader_file:
        header = '#pragma once\n' + ('#define ' + shader_path.replace('.', '_').upper() + ' "' + shader_file.read() + '"').replace('\n', '\\n\\\n')

        with open(shader_path + '.h', 'w') as header_file:
            header_file.write(header)
