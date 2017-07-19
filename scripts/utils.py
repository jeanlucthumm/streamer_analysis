def get_name_data(name: str):
    parts = name.split('-')
    if len(parts) != 2 or parts[1] not in ['s', 'o']:
        return None
    else:
        return parts[0], parts[1]
