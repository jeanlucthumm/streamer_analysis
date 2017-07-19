class DataPoint:
    """
    A data point with streamer angle data for observed and simulated images
    """

    def __init__(self, name):
        self.name = name
        self.s = []
        self.o = []

    def __str__(self):
        return '{' + self.name + ':' + str(self.s) + ',' + str(self.o) + '}'


def get_name_data(name: str):
    """
    Split and validate a name string into relevant information
    :param name: name of the image
    :return: (prefix, 'o'/'s') or None if name is invalid
    """
    base_name = name.split('.')[0]
    parts = base_name.split('-')
    if len(parts) != 2 or parts[1] not in ['s', 'o']:
        return None
    else:
        return parts[0], parts[1]


def populate_table(table: {str: DataPoint}, parts: (str, str), angles: []):
    """
    Populates with one entry, a lookup table containing DataPoints
    :param table: {name, DataPoint(name)}
    :param parts: (prefix, 'o'/'s') where prefix is base name,
    'o' is observed, and 's' is simulated
    :param angles: list of streamer angles (rads) found in image
    :return: True if no errors were encountered, False otherwise
    """
    name = parts[0]
    kind = parts[1]

    if name in table:
        data_point = table[name]
    else:
        data_point = DataPoint(name)
        table[name] = data_point

    no_error = True
    if kind == 's':
        for angle in angles:
            try:
                data_point.s.append(float(angle))
            except ValueError:
                print('could not convert angle:', angle, 'for prefix:', name)
                no_error = False
    elif kind == 'o':
        for angle in angles:
            try:
                data_point.o.append(float(angle))
            except ValueError:
                print('could not convert angle:', angle, 'for prefix:', name)
                no_error = False

    return no_error


def get_streamer_delta(data_point: DataPoint, threshold):
    """
    Finds correlated streamer angles and computes the difference between them
    :param data_point: DataPoint containing streamer angles
    :param threshold: used to determine correlation
    :return: list of angle deltas (simulated - observed)
    """
    result = []
    for s_angle in data_point.s:
        for o_angle in data_point.o:
            delta = s_angle - o_angle
            if abs(delta) <= threshold:
                result.append(round(delta, 10))
    return result
