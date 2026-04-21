"""
Problem (The Commons): Dividing a list of people into teams fairly is notoriously difficult. 
Usually, one team ends up overloaded with highly skilled people while the other struggles.
Logic: The Snake Draft Algorithm. We sort the pool of users by their objective skill rating 
(highest to lowest). We then distribute them back and forth (1, 2, 2, 1, 1, 2) to ensure the 
average weight of both teams remains mathematically balanced.
"""

class User:
    def __init__(self, name, skill_rating):
        self.name = name
        self.skill = skill_rating

def generate_fair_teams(player_pool, num_teams):
    # Sort players purely by skill descending
    sorted_players = sorted(player_pool, key=lambda x: x.skill, reverse=True)
    
    teams = [[] for _ in range(num_teams)]
    team_scores = [0] * num_teams
    
    # Snake draft logic
    direction = 1
    current_team = 0
    
    for player in sorted_players:
        teams[current_team].append(player)
        team_scores[current_team] += player.skill
        
        current_team += direction
        
        # If we hit the bounds, reverse direction but stay on the same team for one turn
        if current_team == num_teams or current_team == -1:
            direction *= -1
            current_team += direction
            
    return teams, team_scores

if __name__ == "__main__":
    print("\033[1m\n--- FairMatch Allocator ---\033[0m")
    
    pool = [
        User("Ali", 95), User("Saad", 92), User("Omar", 88),
        User("Bilal", 80), User("Zaid", 75), User("Hassan", 70),
        User("Tariq", 65), User("Hamza", 60)
    ]
    
    print("\033[90mDrafting 8 players into 2 teams using Snake Draft Algorithm...\033[0m\n")
    
    teams, scores = generate_fair_teams(pool, 2)
    
    for i in range(len(teams)):
        print(f"  \033[1mTeam {i+1}\033[0m \033[90m(Total Skill: {scores[i]})\033[0m")
        roster = ", ".join([f"{p.name} [{p.skill}]" for p in teams[i]])
        print(f"    Members: \033[36m{roster}\033[0m\n")