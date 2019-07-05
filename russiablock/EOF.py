try:
    34786 / 0
except ZeroDivisionError:
    try:
        raise SyntaxError('Division by zero')
    except:
        try:
            raise TypeError('Division by zero')
        except:
            try:
                raise NameError('Division by zero')
            except:
                raise EOFError('Division by zero')
        

    
        
