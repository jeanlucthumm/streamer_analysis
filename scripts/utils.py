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
