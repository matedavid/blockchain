from flask import Flask
from Database import Database

app = Flask(__name__)

database = Database("./database.csv")

@app.route("/api/getNodes", methods=["GET"])
def getNodes():
    nodes = database.getAll()
    print(nodes)
    resStr = ""
    for node in nodes:
        resStr += f'{node[1]},{node[2]},{node[3]};'
    return resStr

@app.route("/api/newNode")
def newNode():
    pass 


if __name__ == "__main__":
    app.run(debug=True)
