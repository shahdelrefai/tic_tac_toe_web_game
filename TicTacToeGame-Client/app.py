import socket
from flask import Flask, render_template, session, request, redirect, url_for, jsonify

socket_fd = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)
socket_fd.connect(("127.0.0.1", 2176))
print("python connected to C server")

def main():
    message = "python connected"
    socket_fd.send(message.encode())


app = Flask(__name__)


@app.route("/", methods=['GET', 'POST'])
def game():
    if request.method == 'GET':
        return render_template("getnames.html")
    elif request.method == 'POST':
        socket_fd.send(str("r").encode())
        print("move sent : r")

        response = socket_fd.recv(3).decode()
        print(response)

        name1 = request.form.get("name1")
        name2 = request.form.get("name2")

        return render_template("index.html", name1=name1, name2=name2)



@app.route('/api/make_move', methods=['POST'])
def make_move():
    move = request.json
    socket_fd.send(str(move).encode())
    print("move sent : ", move)

    response = socket_fd.recv(3).decode()
    print(response)

    return jsonify(response)


if __name__ == '__main__':
    main()
    app.run()
