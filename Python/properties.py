class Items:
    def __init__(self, count) -> None:
        self.count = count

    @property
    def number(self):
        return self._count
    
    @number.setter
    def number(self, value):
        if value < 0:
            raise Exception("Item count must not be negative!")
        self._count = value
