"""A module for round race.
Version:1.5.0(For python 3.6+)"""
def meet(different_dictence, long, a_speed, b_speed, times):
      """
      different_dictence ---------- Two people's distence.
      long ---------- The round road's long.
      a_speed ---------- The first person's speed.
      b_speed ---------- The second person's speed.
      times ---------- The quantity.
      """
      if different_dictence == 0:
            meet_range = long
            meet_time = long / (a_speed + b_speed)
            print("Meet range: %f" % meet_range)
            print("Meet time: %f" % meet_time)
            print()
      elif different_dictence * 2 == long:
            first_meet_range = long / 2
            first_meet_time = first_meet_range / (a_speed + b_speed)
            other_meet_range = long
            other_meet_time = long / (a_speed + b_speed)
            print("First meet range: %f" % first_meet_range)
            print("First meet time: %f" % first_meet_time)
            print("Other meet range: %f" % (other_meet_range * times))
            print("Other meet time: %f" % (other_meet_time * times))
            print()
      else:
            a_first_meet_range = different_dictence
            b_first_meet_range = long - different_dictence
            a_first_meet_time = a_first_meet_range / (a_speed + b_speed)
            b_first_meet_time = b_first_meet_range / (a_speed + b_speed)
            other_meet_range = long
            other_meet_time = long / (a_speed + b_speed)
            print("First meet range: %f or %f" % (a_first_meet_range, b_first_meet_range))
            print("First meet time: %f or %f" % (a_first_meet_time, b_first_meet_time))
            print("Other meet range: %f" % (other_meet_range * times))
            print("Other meet time: %f" % (other_meet_time * times))
            print()
            
def trace(different_dictence, long, a_speed, b_speed, times):
      """
      different_dictence ---------- Two people's distence.
      long ---------- The round road's long.
      a_speed ---------- The first person's speed.
      b_speed ---------- The second person's speed.
      times ---------- The quantity.
      """
      if different_dictence == 0:
            trace_time = long / (a_speed - b_speed)
            if a_speed > b_speed:
                  trace_range = long + trace_time * b_speed * 2
            elif a_speed < b_speed:
                  trace_range = long + trace_time * a_speed * 2
            else:
                  return 0
            print("Trace range: %f" % abs(trace_range))
            print("Trace time: %f" % abs(trace_time))
            print()
      elif different_dictence * 2 == long:
            first_trace_time = different_dictence / (a_speed - b_speed)
            if a_speed > b_speed:
                  first_trace_range = long / 2 + first_trace_time * b_speed * 2
                  other_trace_range = long + first_trace_time * b_speed * 2
                  other_trace_time = other_trace_range / (a_speed - b_speed)
            elif a_speed < b_speed:
                  first_trace_range = long / 2 + first_trace_time * a_speed * 2
                  other_trace_range = long + first_trace_time * a_speed * 2
                  other_trace_time = other_trace_range / (a_speed - b_speed)
            else:
                  return 0
            print("First trace range: %f" % abs(first_trace_range))
            print("First trace time: %f" % abs(first_trace_time))
            print("Other trace range: %f" % (abs(other_trace_range * times)))
            print("Other trace time: %f" % (abs(other_trace_time * times)))
            print()
      else:
            a_first_trace_time = different_dictence / (a_speed - b_speed)
            b_first_trace_time = long - different_dictence / (a_speed - b_speed)
            if a_speed > b_speed:
                  a_first_trace_range = different_dictence + a_first_trace_time * b_speed * 2
                  other_trace_range = long + a_first_trace_time * b_speed * 2
                  other_trace_time = other_trace_range / (a_speed - b_speed)
            elif a_speed < b_speed:
                  b_first_trace_range = long - different_dictence + b_first_trace_time * a_speed * 2
                  other_trace_range = long + b_first_trace_time * a_speed * 2
                  other_trace_time = other_trace_range / (a_speed - b_speed)
            else:
                  return 0
            if a_speed > b_speed:
                  print("First trace range: %f" % (abs(a_first_trace_range)))
                  print("First trace time: %f" % (abs(a_first_trace_time)))
            else:
                  print("First trace range: %f" % (abs(b_first_trace_range)))
                  print("First trace time: %f" % (abs(b_first_trace_time)))
            print("Other trace range: %f" % (abs(other_trace_range * times)))
            print("Other trace time: %f" % (abs(other_trace_time * times))) 
            print()

if __name__ == "__main__":
      meet(0,600,70,60,5)
      meet(300,600,70,60,5) 
      meet(300,650,70,60,5)
      print()
      trace(0,600,70,60,5)
      trace(0,600,60,70,5)
      trace(300,600,70,60,5)
      trace(300,600,60,70,5)
      trace(300,650,70,60,5)
      trace(300,650,60,70,5)
      




      
