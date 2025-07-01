import sys
import json
from os import path

cpp_source_beggining = """
namespace DarkMatter::EmbeddedResources 
{
"""

cpp_source_ending = """
} // End of DarkMatter::EmbeddedResources namespace
"""

def to_cpp_data(varname, abs_path):
	if not path.exists(abs_path):
		print(f"{abs_path} doesn't exist!")
		exit(-1)
	
	with open(abs_path, "rb") as f:
		data  = f.read()

	hex_bytes = ', '.join(f"0x{int(b):02x}" for b in data)
	return f"""
	static constexpr unsigned char {varname}_data[] = {{ {hex_bytes} }};
	const unsigned char* const {varname} = {varname}_data;
	const unsigned long long {varname}_size = {len(data)}ull;
	"""
		

def main(target, resources_json):
	with open(resources_json, "r") as f:
		resources = json.load(f)
	
	targetFile = open(target, "w")
	targetFile.write(cpp_source_beggining)

	for file in resources:
		print(f"Embedding {file}")
		targetFile.write(to_cpp_data(file, resources[file]["absolute_path"]))


	targetFile.write(cpp_source_ending)
	targetFile.close()

if __name__ == '__main__':
	if len(sys.argv) != 3:
		print("USAGE: EmbedResource.py TARGET_FILE RESOURCES_JSON")
		sys.exit(-1)

	main(sys.argv[1], sys.argv[2])