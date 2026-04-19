"""
Problem: Writing full SQL database queries during early software testing is overkill. 
We need a lightweight, in-memory mock database that understands basic SQL syntax.
Logic: A Dictionary of Lists of Dictionaries. We parse text commands (INSERT, SELECT), 
extract the keys and values, and manipulate our Python objects to mimic real database behavior.
"""

class MiniDatabase:
    def __init__(self):
        # Format: {'users': [{'id': '1', 'name': 'ali'}], 'orders': [...] }
        self.tables = {}

    def execute(self, query):
        tokens = query.strip().split()
        if not tokens: return

        command = tokens[0].upper()

        try:
            if command == "CREATE" and tokens[1].upper() == "TABLE":
                table_name = tokens[2]
                if table_name not in self.tables:
                    self.tables[table_name] = []
                    print(f"  \033[32m✓ Table '{table_name}' created.\033[0m")
                else:
                    print(f"  \033[31mTable '{table_name}' already exists.\033[0m")

            elif command == "INSERT" and tokens[1].upper() == "INTO":
                table_name = tokens[2]
                if table_name not in self.tables:
                    print(f"  \033[31mTable '{table_name}' does not exist.\033[0m")
                    return
                
                # Simple parsing assuming format: INSERT INTO users id=1 name=ali
                record = {}
                for token in tokens[3:]:
                    key, value = token.split('=')
                    record[key] = value
                
                self.tables[table_name].append(record)
                print(f"  \033[32m✓ 1 row inserted into '{table_name}'.\033[0m")

            elif command == "SELECT" and tokens[1] == "*" and tokens[2].upper() == "FROM":
                table_name = tokens[3]
                if table_name not in self.tables:
                    print(f"  \033[31mTable '{table_name}' does not exist.\033[0m")
                    return
                
                records = self.tables[table_name]
                if not records:
                    print(f"  \033[90m(Empty set)\033[0m")
                    return
                
                print(f"\n  \033[1m--- {table_name} Data ---\033[0m")
                for i, row in enumerate(records):
                    formatted_row = ", ".join(f"{k}: {v}" for k, v in row.items())
                    print(f"  Row {i+1} | {formatted_row}")
                print("")

            else:
                print("  \033[31mSyntax Error or Unsupported Command. Supported: CREATE TABLE, INSERT INTO, SELECT * FROM\033[0m")

        except Exception as e:
            print("  \033[31mQuery execution failed. Check your syntax.\033[0m")

if __name__ == "__main__":
    db = MiniDatabase()
    print("\033[1m\n--- In-Memory SQL Engine ---\033[0m")
    print("\033[90mSupported Commands:\033[0m")
    print("\033[90m  CREATE TABLE users\033[0m")
    print("\033[90m  INSERT INTO users id=1 role=admin\033[0m")
    print("\033[90m  SELECT * FROM users\033[0m")
    print("\033[90mType 'exit' to quit.\033[0m\n")

    while True:
        try:
            query = input("\033[1msql> \033[0m").strip()
            if query.lower() == 'exit': break
            if query: db.execute(query)
        except EOFError:
            break
        except KeyboardInterrupt:
            break