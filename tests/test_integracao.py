# Arthur Maziviero Faria - RM 573928
# Jun Uehara - RM 570537
# Felipe de Souza Gallo - RM 569680
# Roberson Reguero Luiz Junior - RM 573031
# Tommaso Conceissao Nagliatti - RM 572147
# Matheus Martins Lacerda - RM 570843 (representante)
"""Teste HTTP usando a ponte original e o executavel compilado."""
import importlib.util
import json
from pathlib import Path
import threading
from urllib.request import Request, urlopen
from urllib.error import HTTPError

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location("ponte", ROOT / "bridge/bridge.py")
ponte = importlib.util.module_from_spec(spec)
spec.loader.exec_module(ponte)
servidor = ponte.ThreadingHTTPServer(("127.0.0.1", 0), ponte.Handler)
thread = threading.Thread(target=servidor.serve_forever, daemon=True)
thread.start()
base = "http://127.0.0.1:" + str(servidor.server_port)
log = []

def comando(texto, status=200):
    req = Request(base + "/api/command", data=json.dumps({"command": texto}).encode(),
                  headers={"Content-Type": "application/json"})
    try:
        resposta = urlopen(req, timeout=10)
    except HTTPError as exc:
        resposta = exc
    with resposta:
        assert resposta.status == status
        dados = json.load(resposta)
    log.append(texto + " => HTTP " + str(status) + " | " + dados["raw"])
    return dados

try:
    for arquivo in ("/", "/style.css", "/app.js", "/api/ping"):
        with urlopen(base + arquivo, timeout=10) as resposta:
            assert resposta.status == 200
        log.append("GET " + arquivo + " => HTTP 200")
    s = comando("INIT 3")["state"]
    assert s["A"] == [1, 2, 3] and s["B"] == [] and s["C"] == []
    comando("MOVE B C", 422)
    assert comando("STATE")["state"] == s
    comando("MOVE A A", 422)
    comando("MOVE X C", 422)
    assert comando("STATE")["state"] == s
    s = comando("MOVE A C")["state"]
    assert s["C"] == [1] and s["MOVES"] == 1
    comando("MOVE A C", 422)
    assert comando("STATE")["state"] == s
    assert len(comando("HISTORY")["history"]) == 1
    comando("RESET 3")
    movimentos = [("A", "C"), ("A", "B"), ("C", "B"), ("A", "C"),
                  ("B", "A"), ("B", "C"), ("A", "C")]
    discos = [1, 2, 1, 3, 1, 2, 1]
    for origem, destino in movimentos:
        s = comando("MOVE " + origem + " " + destino)["state"]
    assert s["WIN"] == 1 and s["MOVES"] == 7 and s["C"] == [1, 2, 3]
    assert s["A"] == [] and s["B"] == []
    esperado = [{"disk": d, "from": o, "to": t}
                for d, (o, t) in zip(discos, movimentos)]
    assert comando("HISTORY")["history"] == esperado
    s = comando("RESET 8")["state"]
    assert s["A"] == list(range(1, 9)) and s["B"] == [] and s["C"] == []
    assert s["MOVES"] == 0 and s["WIN"] == 0
    assert comando("HISTORY")["history"] == []
    comando("INIT 2", 422)
    comando("INIT 9", 422)
    assert comando("STATE")["state"] == s
    log.append("PASSOU: frontend servido, comandos HTTP, regras, historico, reset e vitoria.")
    print("\n".join(log))
finally:
    servidor.shutdown()
    servidor.server_close()
    if ponte.engine is not None:
        ponte.engine.stdin.write("QUIT\n")
        ponte.engine.stdin.flush()
        ponte.engine.wait(timeout=5)
