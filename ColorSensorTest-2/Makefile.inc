# Makefile.inc

# このMakefile.incのあるディレクトリパス取得
mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

# C++ソースファイルのオブジェクトファイルリストにapp.oを追加
APPL_CXXOBJS += \
	app.o \

# ソース言語をC++に指定
SRCLANG := c++

# EV3RTアプリケーションビルド設定がある場合
ifdef CONFIG_EV3RT_APPLICATION

# spikeapiのライブラリを読み込み (パスは環境に合わせて変更してください)
include $(EV3RT_SDK_LIB_DIR)/libcpp-spike/Makefile

endif

# アプリケーションのディレクトリ設定（必要に応じて追加）
APPL_DIRS += $(mkfile_path)app $(mkfile_path)unit

# インクルードパスにappディレクトリを追加
INCLUDES += \
	-I$(mkfile_path)app

