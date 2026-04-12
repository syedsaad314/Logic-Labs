"""
Problem: We have tasks that must be done before others (e.g., A before B). We need to 
find a valid, linear order to complete all tasks without getting stuck in a loop.
Logic: Topological Sorting using Kahn's Algorithm. We track the "in-degree" (how many 
dependencies a task has). We process tasks with 0 dependencies, resolving them and unlocking the next ones.
"""

from collections import defaultdict, deque

def plan_tasks():
    print("\033[1m\n--- Project Dependency Planner ---\033[0m")
    print("\033[90mDefine dependencies. Format: 'TaskA > TaskB' (Task A must be done before Task B)\033[0m")
    print("\033[90mType 'run' to calculate the schedule.\033[0m\n")

    graph = defaultdict(list)
    in_degree = defaultdict(int)
    all_tasks = set()

    while True:
        try:
            line = input("\033[1m> \033[0m").strip()
            if line.lower() == 'run':
                break
            
            if ' > ' in line:
                pre_req, task = line.split(' > ')
                pre_req, task = pre_req.strip(), task.strip()
                
                graph[pre_req].append(task)
                in_degree[task] += 1
                
                all_tasks.add(pre_req)
                all_tasks.add(task)
            else:
                print("  \033[31mInvalid format. Use: PreReq > Task\033[0m")
        except EOFError:
            break

    # Find tasks with no prerequisites to start the queue
    queue = deque([t for t in all_tasks if in_degree[t] == 0])
    scheduled_order = []

    while queue:
        current = queue.popleft()
        scheduled_order.append(current)

        for dependent_task in graph[current]:
            in_degree[dependent_task] -= 1
            if in_degree[dependent_task] == 0:
                queue.append(dependent_task)

    print("\n\033[1mExecution Plan:\033[0m")
    if len(scheduled_order) == len(all_tasks):
        for i, task in enumerate(scheduled_order):
            print(f"  {i+1}. {task}")
    else:
        print("  \033[31mError: Dependency cycle detected. This project is impossible to complete.\033[0m")

if __name__ == "__main__":
    plan_tasks()