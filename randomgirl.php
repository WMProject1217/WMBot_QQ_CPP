<?php
/*
从 "随机老婆[花酱随机老婆草] By 花开花落 版本 0.0.1" 重写
WMProject1217 Studios 2022
Last Fix on 2022-1-26
*/
    $加减判断 = rand(0,10);
    if ($加减判断 < 6) {
        $老婆变换身高 = rand(0,30);
        $老婆身高 = 160 - $老婆变换身高;
    } else {
        if ($加减判断 < 11) {
            $老婆变换身高 = rand(0,26);
            $老婆身高 = 160 + $老婆变换身高;
        }
    }
    $BMI = rand(05,18);
    $身高 = floor($老婆身高) / 100;
    $身高平方 = $身高 * $身高;
    $体重2 = $BMI * $身高平方;
    $体重 = round($体重2 * 2, 2);
    $头发颜色数组 = array("浅粉红 | #FFB6C1","粉红 | #FFC0CB","深红 | #DC143C","淡紫红 | #FFF0F5","弱紫罗兰红 | #DB7093 ","热情的粉红 | #FF69B4","深粉红 | #FF1493","中紫罗兰红 | #C71585","暗紫色 | #DA70D6","蓟色 | #D8BFD8","洋李色 | #DDA0DD","紫罗兰 | #EE82EE","洋红 | #FF00FF","紫红 | #FF00FF","深洋红 | #8B008B","紫色 | #800080","中兰花紫 | #BA55D3","暗紫罗兰 | #9400D3","暗兰花紫 | #9932CC","靛青 | #4B0082","蓝紫罗兰 | #8A2BE2","中紫色 | #9370DB","中暗蓝色 | #7B68EE","石蓝色 | #6A5ACD","暗灰蓝色 | #483D8B","淡紫色 | #E6E6FA","幽灵白 | #F8F8FF","纯蓝 | #0000FF","中蓝色 | #0000CD","午夜蓝 | #191970","暗蓝色 | #00008B","海军蓝 | #000080","宝蓝 | #4169E1","矢车菊蓝 | #6495ED","亮钢蓝 | #B0C4DE","亮蓝灰 | #778899","灰石色 | #708090","闪兰色 | #1E90FF","爱丽丝蓝 | #F0F8FF","钢蓝 | #4682B4","亮天蓝色 | #87CEFA","天蓝色 | #87CEEB","深天蓝 | #00BFFF","亮蓝 | #ADD8E6","粉蓝色 | #B0E0E6","军兰色 | #5F9EA0","蔚蓝色 | #F0FFFF","淡青色 | #E0FFFF","弱绿宝石 | #AFEEEE","青色 | #00FFFF","浅绿色 | #00FFFF","暗绿宝石 | #00CED1","暗瓦灰色 | #2F4F4F","暗青色 | #008B8B","水鸭色 | #008080","中绿宝石 | #48D1CC","浅海洋绿 | #20B2AA","绿宝石 | #40E0D0","宝石碧绿 | #7FFFD4","中宝石碧绿 | #66CDAA","中春绿色 | #00FA9A","薄荷奶油 | #F5FFFA","春绿色 | #00FF7F","中海洋绿 | #3CB371","海洋绿 | #2E8B57","蜜瓜色 | #F0FFF0","淡绿色 | #90EE90","弱绿色 | #98FB98","暗海洋绿 | #8FBC8F","闪光深绿 | #32CD32","闪光绿 | #00FF00","森林绿 | #228B22","纯绿 | #008000","暗绿色 | #006400","黄绿色 | #7FFF00","草绿色 | #7CFC00","绿黄色 | #ADFF2F","暗橄榄绿 | #556B2F","黄绿色 | #9ACD32","橄榄褐色 | #6B8E23","米色 | #F5F5DC","亮菊黄 | #FAFAD2","象牙色 | #FFFFF0","浅黄色 | #FFFFE0","纯黄 | #FFFF00","橄榄 | #808000","暗黄褐色 | #BDB76B","柠檬绸 | #FFFACD","灰菊黄 | #EEE8AA","黄褐色 | #F0E68C","金色 | #FFD700","玉米丝色 | #FFF8DC","金菊黄 | #DAA520","暗金菊黄 | #B8860B","花的白色 | #FFFAF0","老花色 | #FDF5E6","浅黄色 | #F5DEB3","鹿皮色 | #FFE4B5","橙色 | #FFA500","番木色 | #FFEFD5","白杏色 | #FFEBCD","纳瓦白 | #FFDEAD","古董白 | #FAEBD7","茶色 | #D2B48C","硬木色 | #DEB887","陶坯黄 | #FFE4C4","深橙色 | #FF8C00","亚麻布 | #FAF0E6","秘鲁色 | #CD853F","桃肉色 | #FFDAB9","沙棕色 | #F4A460","巧克力色 | #D2691E","重褐色 | #8B4513","海贝壳 | #FFF5EE","黄土赭色 | #A0522D","浅鲑鱼肉色 | #FFA07A","珊瑚 | #FF7F50","橙红色 | #FF4500","深鲜肉 | #E9967A","番茄红 | #FF6347","浅玫瑰色 | #FFE4E1","鲜肉 | #FA8072","雪白色 | #FFFAFA","淡珊瑚色 | #F08080","玫瑰棕色 | #BC8F8F","印度红 | #CD5C5C","纯红 | #FF0000","棕色 | #A52A2A","火砖色 | #B22222","深红色 | #8B0000","栗色 | #800000","纯白 | #FFFFFF","白烟 | #F5F5F5","淡灰色 | #DCDCDC","浅灰色 | #D3D3D3","银灰色 | #C0C0C0","深灰色 | #A9A9A9","灰色 | #808080","暗淡的灰色 | #696969","纯黑 | #000000","天依蓝 | #66CCFF");
    $头发颜色随机数 = rand(0, count($头发颜色数组) - 1);
    $头发颜色 = $头发颜色数组[$头发颜色随机数];
    $眼睛颜色数组 = array("浅粉红 | #FFB6C1","粉红 | #FFC0CB","深红 | #DC143C","弱紫罗兰红 | #DB7093 ","热情的粉红 | #FF69B4","深粉红 | #FF1493","中紫罗兰红 | #C71585","暗紫色 | #DA70D6","洋李色 | #DDA0DD","紫罗兰 | #EE82EE","洋红 | #FF00FF","紫红 | #FF00FF","深洋红 | #8B008B","紫色 | #800080","中兰花紫 | #BA55D3","暗紫罗兰 | #9400D3","暗兰花紫 | #9932CC","靛青 | #4B0082","蓝紫罗兰 | #8A2BE2","中紫色 | #9370DB","中暗蓝色 | #7B68EE","石蓝色 | #6A5ACD","暗灰蓝色 | #483D8B","纯蓝 | #0000FF","中蓝色 | #0000CD","午夜蓝 | #191970","暗蓝色 | #00008B","海军蓝 | #000080","宝蓝 | #4169E1","矢车菊蓝 | #6495ED","亮钢蓝 | #B0C4DE","亮蓝灰 | #778899","灰石色 | #708090","闪兰色 | #1E90FF","钢蓝 | #4682B4","亮天蓝色 | #87CEFA","天蓝色 | #87CEEB","深天蓝 | #00BFFF","亮蓝 | #ADD8E6","粉蓝色 | #B0E0E6","军兰色 | #5F9EA0","弱绿宝石 | #AFEEEE","青色 | #00FFFF","浅绿色 | #00FFFF","暗绿宝石 | #00CED1","暗瓦灰色 | #2F4F4F","暗青色 | #008B8B","水鸭色 | #008080","中绿宝石 | #48D1CC","浅海洋绿 | #20B2AA","绿宝石 | #40E0D0","宝石碧绿 | #7FFFD4","中宝石碧绿 | #66CDAA","中春绿色 | #00FA9A","春绿色 | #00FF7F","中海洋绿 | #3CB371","海洋绿 | #2E8B57","淡绿色 | #90EE90","弱绿色 | #98FB98","暗海洋绿 | #8FBC8F","闪光深绿 | #32CD32","闪光绿 | #00FF00","森林绿 | #228B22","纯绿 | #008000","暗绿色 | #006400","黄绿色 | #7FFF00","草绿色 | #7CFC00","绿黄色 | #ADFF2F","暗橄榄绿 | #556B2F","黄绿色 | #9ACD32","纯黄 | #FFFF00","橄榄 | #808000","暗黄褐色 | #BDB76B","灰菊黄 | #EEE8AA","黄褐色 | #F0E68C","金色 | #FFD700","金菊黄 | #DAA520","暗金菊黄 | #B8860B","浅黄色 | #F5DEB3","鹿皮色 | #FFE4B5","橙色 | #FFA500","纳瓦白 | #FFDEAD","茶色 | #D2B48C","硬木色 | #DEB887","陶坯黄 | #FFE4C4","深橙色 | #FF8C00","秘鲁色 | #CD853F","桃肉色 | #FFDAB9","沙棕色 | #F4A460","巧克力色 | #D2691E","重褐色 | #8B4513","黄土赭色 | #A0522D","浅鲑鱼肉色 | #FFA07A","珊瑚 | #FF7F50","橙红色 | #FF4500","深鲜肉 | #E9967A","番茄红 | #FF6347","鲜肉 | #FA8072","淡珊瑚色 | #F08080","玫瑰棕色 | #BC8F8F","印度红 | #CD5C5C","纯红 | #FF0000","棕色 | #A52A2A","火砖色 | #B22222","深红色 | #8B0000","栗色 | #800000","淡灰色 | #DCDCDC","浅灰色 | #D3D3D3","银灰色 | #C0C0C0","深灰色 | #A9A9A9","灰色 | #808080","暗淡的灰色 | #696969","纯黑 | #000000");
    $眼睛颜色随机数 = rand(0, count($眼睛颜色数组) - 1);
    $眼睛颜色 = $眼睛颜色数组[$眼睛颜色随机数];
    $罩杯数组 = array("A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z","A","B","C","D","E","F","G","H","A","B","C","D","E","F","G","A","B","C","D","E","F","A","B","C","D","E","A","B","C","D","E","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","B","B","B","B","B","B","B","B","B","B","B","B","B","B","B","B","B","B","B","C","C","C","C","C","C","C","C","C","C","C","C","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A");
    $罩杯随机数 = rand(0, count($罩杯数组) - 1);
    $罩杯 = $罩杯数组[$罩杯随机数];
    $加减判断 = rand(0, 10);
    if ($加减判断 < 6) {
        $老婆变换三围1 = rand(0, 5);
        $老婆三围1 = 84 - $老婆变换三围1;
    } else {
        if ($加减判断 < 11) {
            $老婆变换三围1 = rand(0, 5);
            $老婆三围1 = 84 + $老婆变换三围1;
        }
    }
    $加减判断 = rand(0, 10);
    if ($加减判断 < 6) {
        $老婆变换三围2 = rand(0, 5);
        $老婆三围2 = 61 - $老婆变换三围2;
    } else {
        if ($加减判断 < 11) {
            $老婆变换三围2 = rand(0, 5);
            $老婆三围2 = 61 + $老婆变换三围2;
        }
    }
    $加减判断 = rand(0, 10);
    if ($加减判断 < 6) {
        $老婆变换三围3 = rand(0, 5);
        $老婆三围3 = 90 - $老婆变换三围3;
    } else {
        if ($加减判断 < 11) {
            $老婆变换三围3 = rand(0, 5);
            $老婆三围3 = 90 + $老婆变换三围3;
        }
    }
    $发型数组 = array("双马尾","单马尾","高马尾","丸子头","麻花辫","披发","过膝发","条纹发");
    $发型随机数 = rand(0, count($发型数组) - 1);
    $发型 = $发型数组[$发型随机数];
    $加减判断 = rand(0, 100);
    if ($加减判断 < 3) {
        $袜子 = "足";
        $袜子颜色 = "赤";
    } else {
        if ($加减判断 < 101) {
            $袜子数组 = array("裤袜","大腿袜","长筒袜","过膝袜","及膝袜","短筒袜","泡泡袜","短袜","船袜");
            $袜子随机数 = rand(0, count($袜子数组) - 1);
            $袜子颜色数组 = array("白色","黑色","肉色","蓝白条纹","粉白条纹","黑白条纹","黑色条纹","白色条纹","白色花边","黑色花边","灰色条纹");
            $袜子颜色随机数 = rand(0, count($袜子颜色数组) - 1);
            $袜子 = $袜子数组[$袜子随机数];
            $袜子颜色 = $袜子颜色数组[$袜子颜色随机数];
        }
    }
    if (floor($老婆身高) < 141) {
        $年龄数组 = array("8","9","10");
        $年龄随机数 = rand(0, count($年龄数组) - 1);
        $年龄 = $年龄数组[$年龄随机数];
        if ($体重 > 60) {
            $体重 = round($体重 / 2, 2);
        } else if ($体重 < 20) {
            $体重 = round($体重 * 2, 2);
        } 
    } elseif (floor($老婆身高) < 151) {
        $年龄数组 = array("11","12","13");
        $年龄随机数 = rand(0, count($年龄数组) - 1);
        $年龄 = $年龄数组[$年龄随机数];
        if ($体重 > 70) {
            $体重 = round($体重 / 2, 2);
        } else if ($体重 < 24) {
            $体重 = round($体重 * 2, 2);
        } 
    } elseif (floor($老婆身高) < 156) {
        $年龄数组 = array("12","13","14");
        $年龄随机数 = rand(0, count($年龄数组) - 1);
        $年龄 = $年龄数组[$年龄随机数];
        if ($体重 > 80) {
            $体重 = round($体重 / 2, 2);
        } else if ($体重 < 32) {
            $体重 = round($体重 * 2, 2);
        } 
    } elseif (floor($老婆身高) < 161) {
        $年龄数组 = array("13","14","15");
        $年龄随机数 = rand(0, count($年龄数组) - 1);
        $年龄 = $年龄数组[$年龄随机数];
        if ($体重 > 90) {
            $体重 = round($体重 / 2, 2);
        } else if ($体重 < 42) {
            $体重 = round($体重 * 2, 2);
        } 
    } elseif (floor($老婆身高) < 166) {
        $年龄数组 = array("14","15","16");
        $年龄随机数 = rand(0, count($年龄数组) - 1);
        $年龄 = $年龄数组[$年龄随机数];
        if ($体重 > 80) {
            $体重 = round($体重 / 2, 2);
        } else if ($体重 < 32) {
            $体重 = round($体重 * 2, 2);
        } 
    } elseif (floor($老婆身高) < 171) {
        $年龄数组 = array("15","16","17");
        $年龄随机数 = rand(0, count($年龄数组) - 1);
        $年龄 = $年龄数组[$年龄随机数];
        if ($体重 > 90) {
            $体重 = round($体重 / 2, 2);
        } else if ($体重 < 42) {
            $体重 = round($体重 * 2, 2);
        } 
    } elseif (floor($老婆身高) < 176) {
        $年龄数组 = array("16","17","18");
        $年龄随机数 = rand(0, count($年龄数组) - 1);
        $年龄 = $年龄数组[$年龄随机数];
        if ($体重 > 90) {
            $体重 = round($体重 / 2, 2);
        } else if ($体重 < 42) {
            $体重 = round($体重 * 2, 2);
        } 
    } elseif (floor($老婆身高) < 181) {
        $年龄数组 = array("17","18","19");
        $年龄随机数 = rand(0, count($年龄数组) - 1);
        $年龄 = $年龄数组[$年龄随机数];
        if ($体重 > 90) {
            $体重 = round($体重 / 2, 2);
        } else if ($体重 < 42) {
            $体重 = round($体重 * 2, 2);
        } 
    } else {
        if (floor($老婆身高) < 186) {
            $年龄数组 = array("20","21","22");
            $年龄随机数 = rand(0, count($年龄数组) - 1);
            $年龄 = $年龄数组[$年龄随机数];
            if ($体重 > 120) {
                $体重 = round($体重 / 2, 2);
            } else if ($体重 < 48) {
                $体重 = round($体重 * 2, 2);
            } 
        } else {
            $年龄 = rand(400,410);
            $体重 = round(rand(4000,5000) / 100, 2);;
            $老婆三围1 = rand(52,66);
            $老婆三围2 = rand(54,62);
            $老婆三围3 = rand(56,66);
            $罩杯 = "B";
            $头发颜色 = "纯白 | #FFFFFF";
            $眼睛颜色 = "血红 | #EF0000";
            $袜子颜色 = "蓝色条纹";
            $袜子 = "长筒袜";
            $发型 = "过膝发";
        }
    }
    echo "<pre>这是 #username# 生成的老婆属性喵：" . "\n身高：" . $老婆身高 . "cm"  . " 体重：" . $体重 . "kg"  . " 年龄：" . $年龄  . "\n胸围：" . $老婆三围1 . "cm"  . " 腰围：" . $老婆三围2 . "cm"  . " 臀围：" . $老婆三围3 . "cm"  . " 罩杯：" . $罩杯  . "\n头发颜色：" . $头发颜色  . " 眼睛颜色：" . $眼睛颜色  . " 袜子：" . $袜子颜色 . $袜子  . " 发型：" . $发型 .  "</pre>";
?>