import chess
import chess.engine

engine = chess.engine.SimpleEngine.popen_uci("/usr/bin/stockfish")

board = chess.Board()
# info = engine.analyse(board, chess.engine.Limit(time=0.1, depth=))
# print("Score:", info)
# Score: PovScore(Cp(+20), WHITE)

board = chess.Board("r1bqkbnr/p1pp1ppp/1pn5/4p3/2B1P3/5Q2/PPPP1PPP/RNB1K1NR w KQkq - 2 4")
info = engine.play(board, chess.engine.Limit(depth=20))
print("Score:", info)
# Score: PovScore(Mate(+1), WHITE)

print(board)

engine.quit()