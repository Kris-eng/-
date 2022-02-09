from selenium import webdriver
import ddddocr
import cv2
from PIL import Image
import time
from selenium.webdriver.support.ui import Select
bro = webdriver.Chrome(executable_path='chromedriver.exe')
bro.get('http://xg.sylu.edu.cn/spcp/web')
ocr = ddddocr.DdddOcr()
# with open('testt.png', 'rb') as f:
#     img_bytes = f.read()
# res = ocr.classification(img_bytes)
bro.save_screenshot('aa.png')
code_img = bro.find_element_by_xpath('//*[@id="code-box"]')
location = code_img.location
size = code_img.size
# code_img.
print(size)
print(location)
print(location['x'])
rangle = (
int(location['x']*1.25), int(location['y']*1.25), int((location['x'] + size['width'])*1.25), int((location['y'] + size['height']))*1.25)

i = Image.open('./aa.png')
print(i.size)
code_img_name = './code.png'
#crop根据指定区域进行图片裁剪
frame = i.crop(rangle)
frame.save(code_img_name)
with open('code.png', 'rb') as f:
    img_bytes = f.read()
res = ocr.classification(img_bytes)

print(res)


bro.find_element_by_id('StudentId').send_keys('2003070227')
# time.sleep(2)
bro.find_element_by_id('Name').send_keys('30201x')
# time.sleep(2)
bro.find_element_by_id('codeInput').send_keys(res)
# time.sleep(2)
bro.find_element_by_id('Submit').click()
# time.sleep(2)
bro.find_element_by_id('platfrom2').click()
# time.sleep(2)
s1 = Select(bro.find_element_by_name('County'))  # 实例化Select
s1.select_by_index(7)

bro.execute_script('window.scrollTo(0,document.body.scrollHeight)')
time.sleep(2)

ocr = ddddocr.DdddOcr()
# with open('testt.png', 'rb') as f:
#     img_bytes = f.read()
# res = ocr.classification(img_bytes)
bro.save_screenshot('bb.png')
code_img = bro.find_element_by_xpath('//*[@id="code-box"]')
print(code_img.location)
location = code_img.location
size = code_img.size
# code_img.
print(size)
print(location)
print(location['x'])
rangle = (
int(1110), int(610), int(1220), int(650))

i = Image.open('./bb.png')
print(i.size)
code_img_name = './code2.png'


frame = i.crop(rangle)
frame.save(code_img_name)
with open('code2.png', 'rb') as f:
    img_bytes = f.read()
res = ocr.classification(img_bytes)
print(res)
bro.find_element_by_id('VCcode').send_keys(res)
time.sleep(2)
bro.find_element_by_id('ckCLS').click()
time.sleep(2)
bro.find_element_by_id('SaveBtnDiv').click()