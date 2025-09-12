from pathlib import Path

paths = [Path("cute/src"), Path("cute/include")]

def replace(filepath):
	with open(filepath) as file:
		content:str  = file.read()

	content = content.replace("Container", "CuteAtom")
	content = content.replace("con", "atom")

	with open(filepath, "w") as file:
		file.write(content)




for path in paths:
	for item in path.iterdir():
		replace(item)
		