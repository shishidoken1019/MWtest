<?php

require_once('config.inc');
require_once('crypt_factory.inc');

class crypt_factory {

	static public function get_instance($f) {
		// 取り込み
		$conf = new config;
		$conf->set_file($f);

		// 暗号化アルゴリズムのチョイス
		$crypt_type = $conf->find('type');
		if (strcasecmp($crypt_type, "MCRYPT_RIJNDAEL_256") === 0) {
			require_once('crypt_rijndael256.inc');
			$conn = new crypt_rijndael256;
		}
		else {
			// 判別不能なのでエラー復帰
			return null;
		}

		// 設定
		$conn->set_key($conf->find('key'));
		$conn->set_block_mode($conf->find('block_mode'));

		return $conn;
	}

}

