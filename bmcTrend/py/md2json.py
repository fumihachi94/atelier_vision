
import sys
import re
import logging
logging.basicConfig(
    format="%(message)s", stream=sys.stderr, level=logging.INFO)
from datetime import datetime
import json

key_list = [
    'Tesla',
    'Nio',
    'Ford',
    'BMW',
    'Audi',
    'VW',
    'Mercedes',
    'Mazda',
    'Toyota',
    'Honda',
    'Nissan',
    'Bosch', 
    'Other']

def save_as_json(date, category, title, body, path):
    d_json = {'date':date.strftime('%Y-%m-%d'), 'category':category, 'title':title, 'body':body}
    print(d_json)

    save_file_name = date.strftime('%y%m%d') + '_' + category + '_' + title.replace(" ", "_").replace("/", "_") + '.json'
    if path[-1] == '/':
        save_path = path + save_file_name
    else:
        save_path = path + '/' + save_file_name

    print(save_path)
    with open(save_path, 'w') as fjs:
        json.dump(d_json, fjs, indent=2, ensure_ascii=False)

def get_markdown_article(markdown_file, save_path):
    date = 0
    category = ""
    title = ""
    body = ""
    try:
        body = []
        # mdファイルを1行ずつ読み込む
        with open(markdown_file, 'r') as f:
            dl = f.readlines()
            for d in dl:
                # 見出しを抽出
                if d[0] == '#':
                    # 日付を抽出
                    date_serch = re.search(r'\d{4}/\d{2}/\d{2}', d)
                    if date_serch:
                        date = datetime.strptime(date_serch.group(), '%Y/%m/%d').date()
                        # print(date)
                    # 記事を抽出
                    if '##' in d:
                        # 前の記事をjsonに保存
                        if len(title)>1:
                            save_as_json(date, category, title, body, save_path)
                        # 本文の初期化
                        body = []
                        title = ""
                        # タイトル
                        title = d[d.rfind('#')+2:-1]
                        # カテゴリの分類
                        for key in key_list:
                            if key in title:
                                category = key
                                break
                            else:
                                category = 'Other'
                        title = d[d.rfind(':')+2:-1]
                        print(title, ' - ', category)
                else:
                    body.append(d)
            return 1
    except:
        logging.error("Error: Can't open {0} for reading".format(
            markdown_file))
        sys.exit(1)
    # finally:
    #     f.close()

get_markdown_article('2020-01-18-bmc.md', save_path='../db')