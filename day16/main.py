from typing import List, Tuple

def compare(left, right):
  # convert integers to lists
  if isinstance(left, int):
    left = [left]
  if isinstance(right, int):
    right = [right]

  # handle empty lists
  if not left:
    return True
  if not right:
    return False

  # compare lists
  for l, r in zip(left, right):
    if isinstance(l, int) and isinstance(r, int):
      # compare integers
      if l < r:
        return True
      elif l > r:
        return False
    elif isinstance(l, list) and isinstance(r, list):
      # compare lists
      if compare(l, r):
        return True
      elif compare(r, l):
        return False
  # lists are the same or one list has run out of items
  return len(left) < len(right)

def count_right_order_pairs(packets: List[List[int]]) -> int:
  # helper function for DFS
  def dfs(left: List[int], right: List[int]) -> bool:
    if not left and not right:
      return True
    if not left or not right:
      return False
    if isinstance(left[0], int) and isinstance(right[0], int):
      if left[0] < right[0]:
        return True
      elif left[0] > right[0]:
        return False
      else:
        return dfs(left[1:], right[1:])
    elif isinstance(left[0], int):
      return dfs(left, [right[0]] + right[1:])
    elif isinstance(right[0], int):
      return dfs([left[0]] + left[1:], right)
    else:
      return dfs(left[1:], right[1:])
  
  # count right-order pairs
  count = 0
  for left, right in packets:
    if dfs(left, right):
      count += 1
  return count



def read_packets(file_name):
  # open file and read lines
  with open(file_name, 'r') as file:
    lines = file.readlines()

  # remove newline characters and split lines into pairs
  packets = []
  pair = []
  for line in lines:
    line = line.strip()
    if line:
      # add non-empty lines to the current pair
      pair.append(line)
    else:
      # add the current pair to the list of packets
      packets.append(pair)
      pair = []

  # add the final pair to the list of packets (if there is one)
  if pair:
    packets.append(pair)

  # parse packets into left and right packets
  packets = [[eval(packet[0]), eval(packet[1])] for packet in packets]

  return packets


packets = read_packets('day16/input.txt')
print(count_right_order_pairs(packets))  # should print 13
