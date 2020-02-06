def one_ship(distence, first_disadvantage_time, second_disadvantage_time, first_advantage_time):
      """
      distance ---------- The two place's distance.
      first_disadvantage_time ---------- The first boat's disadvantage oneway_trip's time.
      second_disadvantage_time ---------- The second boat's disadvantage oneway_trip's time.
      first_advantage_time ---------- The first boat's advantage oneway_trip's time.
      """
      first_advantage_speed = distence / first_advantage_time
      first_disadvantage_speed = distence / first_disadvantage_time
      water_speed = (first_advantage_speed - first_disadvantage_speed) / 2
      second_disadvantage_speed = distence / second_disadvantage_time
      second_advantage_speed = second_disadvantage_speed + 2 * water_speed
      second_advantage_time = distence / second_advantage_speed
      print("The second boat's advantage time is: %f hour." % second_advantage_time)

def two_ship(distence, first_round_time, first_more_time, second_speed):
      """
      distance ---------- The two place's distance.
      first_round_time ---------- The first sboat's round_trip time.
      first_more_time ---------- The first boat's time differece to_and_forth.
      second_speed ---------- The second boat's speed in still water.
      """     
      first_advantage_time = (first_round_time - first_more_time) / 2
      first_disadvantage_time = (first_round_time + first_more_time) / 2
      first_advantage_speed = distence / first_advantage_time
      first_disadvantage_speed = distence / first_disadvantage_time
      water_speed = (first_advantage_speed - first_disadvantage_speed) / 2
      second_advantage_time = distence / (second_speed + water_speed)
      second_disadvantage_time = distence / (second_speed - water_speed)
      second_round_time = second_advantage_time + second_disadvantage_time
      print("The second boat's round time is: %f hour." % second_round_time)

if __name__ == "__main__":
      one_ship(360, 18, 12, 16)
      two_ship(360, 35, 5.5, 15.75)


      

      

      
