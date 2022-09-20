import serial
import sys
import glob

speeds = ['1200','2400', '4800', '9600', '19200', '38400', '57600', '115200']

def serial_ports():

  if sys.platform.startswith('win'):
    ports = ['COM%s' % (i + 1) for i in range(256)]
  elif sys.platform.startswith('linux') or sys.platform.startswith('cygwin'):
    # this excludes your current terminal "/dev/tty"
    ports = glob.glob('/dev/tty[A-Za-z]*')
  elif sys.platform.startswith('darwin'):
    ports = glob.glob('/dev/tty.*')
  else:
    raise EnvironmentError('Unsupported platform')

  result = []
  for port in ports:
    try:
      s = serial.Serial(port)
      s.close()
      result.append(port)
    except (OSError, serial.SerialException):
      pass
  return result

ports = ["sf", "sd", "ss"]
print(str(len(ports))+" вариантов:")
for i in range(1, len(ports)+1):
  print("  "+str(i)+") " + ports[i-1])
print("Выберите порт (по умолчанию=1): ", end="")
port = input()
if(port==""):
  port = 1
port = ports[int(port)-1]

baudrate = input("Скорость: ")

# s = serial.Serial(baudrate= baudrate, port=port)

import chess

engine = chess.uci.popen_engine("/usr/bin/stockfish")
engine.uci()
print(engine.name)