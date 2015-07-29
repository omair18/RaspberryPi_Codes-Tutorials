import gspread
gc = gspread.login('email','password')
wks = gc.open("test").sheet1
wks.update_acell('A1',"i don't know but it works :D")
cell_list = wks.range('A1:B7')
