from collections import Counter

class StatisticsCalculator:
    def __init__(self, data):
        if not all(isinstance(x, int) for x in data):
            raise ValueError("All elements must be integers")
        self.data = data

    def mean(self):
        return sum(self.data) / len(self.data) if self.data else None

    def median(self):
        if not self.data:
            return None
        sorted_data = sorted(self.data)
        n = len(sorted_data)
        mid = n // 2
        if n % 2 == 1:
            return sorted_data[mid]
        return (sorted_data[mid - 1] + sorted_data[mid]) / 2

    def mode(self):
        if not self.data:
            return []
        freq = Counter(self.data)
        max_count = max(freq.values())
        return [val for val, cnt in freq.items() if cnt == max_count]

def main():
    try:
        raw = input("Enter integers separated by spaces: ").strip()
        data = list(map(int, raw.split()))
    except ValueError:
        print("Invalid input: please enter only integers.")
        return

    calc = StatisticsCalculator(data)
    print(f"\nMean:   {calc.mean():.2f}")
    print(f"Median: {calc.median():.2f}")
    modes = calc.mode()
    print("Mode" + ("s" if len(modes) > 1 else "") + ":", ", ".join(map(str, modes)))

if __name__ == "__main__":
    main()
