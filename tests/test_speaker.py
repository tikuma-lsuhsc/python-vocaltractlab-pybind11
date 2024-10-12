import vocaltractlab as vtl
from os import getcwd, path

speaker_file = path.join(getcwd(), "vocaltractlab_backend", "resources", "JD3.speaker")
print(speaker_file)

speaker = vtl.Speaker(speaker_file)
print(speaker)

print(speaker.get_glottis_models())

print(speaker.get_selected_glottis())

print(speaker.get_vocal_tract())
