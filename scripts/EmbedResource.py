import sys
import os
from os import path

def generate_content(varname, data):
	hex_bytes = ', '.join(f"0x{int(b):02x}" for b in data)
	return f"""
		#include <cstddef>
		#include "{varname}.h"

		namespace DarkMatter::Embedded
		{{
			const unsigned char {varname}[] = {{
				{hex_bytes}
			}};

			const std::size_t {varname}_len = {len(data)};
		}}
	"""

def main(input_path, output_path, varname):
	with open(input_path, 'rb') as f:
		data = f.read()
	
	cpp_code = generate_content(varname, data)

	with open(output_path, 'w') as out:
		out.write(cpp_code)

	print(f"Successfully generated builtin resource at {output_path}")

if __name__ == '__main__':
	if len(sys.argv) != 4:
		print("USAGE: EmbedResource.py input_file output_file varname")
		sys.exit(-1)

	main(sys.argv[1], sys.argv[2], sys.argv[3])