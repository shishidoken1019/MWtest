<?php

//
ini_set('display_errors', 'on');
error_reporting(E_ALL);
//
//ini_set('display_errors', 'off');

// MW���g����悤�ɂ���
$dir = 'C:\Program Files\Apache Software Foundation\Apache2.2\htdocs\MWtest\MW';
set_include_path(get_include_path() . PATH_SEPARATOR . $dir);

// ��{�I��php.ini�̐ݒ�e��
require_once('mw_set_ini.inc');

// ��f�B���N�g���̐ݒ�
$bp = 'C:\Program Files\Apache Software Foundation\Apache2.2\htdocs\MWtest\HelloWorld\';

// config�t�@�C����
$config       = $bp . 'conf/config.conf';

//
require_once('controller.inc');

//
$co = new controller;
$co->set_base_path($bp);