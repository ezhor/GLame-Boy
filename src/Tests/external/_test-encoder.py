import os
import json

def write_cpu_state(file, object):
    file.write(str(object["a"]) + ",")
    file.write(str(object["b"]) + ",")
    file.write(str(object["c"]) + ",")
    file.write(str(object["d"]) + ",")
    file.write(str(object["e"]) + ",")
    file.write(str(object["f"]) + ",")
    file.write(str(object["h"]) + ",")
    file.write(str(object["l"]) + ",")
    file.write(str(object["pc"]) + ",")
    file.write(str(object["sp"]) + "_")
    for j in range(len(object["ram"])):
        file.write(str(object["ram"][j][0]) + "," + str(object["ram"][j][1]))
        if j < len(object["ram"])-1:
            file.write(",")


with open("./_tests.txt", "w+") as output:
    for root, dirs, files in os.walk(r'.'):
        for file in files:
            if file.endswith('.json'):
                with open(os.path.join(root, file), 'r') as json_file:
                    data = json.load(json_file)
                    for i in range(len(data)):
                        output.write(file + "_" + data[i]["name"] + "_")
                        write_cpu_state(output, data[i]["initial"])
                        output.write("_")
                        write_cpu_state(output, data[i]["final"])
                        output.write("\n")