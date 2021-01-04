package com.imengyu.vr720;

import android.Manifest;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.pm.PackageManager;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.provider.Settings;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.preference.PreferenceManager;

import com.imengyu.vr720.dialog.CommonDialog;
import com.imengyu.vr720.utils.AppUtils;
import com.imengyu.vr720.utils.StorageDirUtils;

public class LunchActivity extends AppCompatActivity {

    private static final int REQUEST_CODE = 179;
    private static final int REQUEST_CODE_SETTINGS = 180;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate( savedInstanceState);

        //设置语言
        SharedPreferences sharedPreferences = PreferenceManager.getDefaultSharedPreferences(this);
        String language = sharedPreferences.getString("language", "");
        AppUtils.setLanguage(this, language);

        VR720Application application = (VR720Application)getApplication();

        //获取参数
        intent = getIntent();

        //
        setContentView(R.layout.activity_lunch);
        new Thread(() -> {
            try {
                Thread.sleep(400);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            //耗时任务，比如加载网络数据
            StorageDirUtils.testAndCreateStorageDirs(getApplicationContext());

            //转回UI线程
            runOnUiThread(() -> {
                application.setInitFinish();
                //检查是否同意许可以及请求权限
                runPermissionAndAgreement();
            });
        }).start();
    }

    private Intent intent = null;

    private void runPermissionAndAgreement() {
        //检查是否同意许可以及请求权限
        AppUtils.testAgreementAllowed(this, (b) -> {
            if(checkPermission())
                runMainActivity();
        });
    }
    // 跳转到主界面
    private void runMainActivity() {

        Intent newIntent = new Intent(LunchActivity.this, MainActivity.class);
        if(intent.hasExtra("openFilePath"))
            newIntent.putExtra("openFilePath", intent.getStringExtra("openFilePath"));
        if(intent.hasExtra("openFileArgPath"))
            newIntent.putExtra("openFileArgPath", intent.getStringExtra("openFileArgPath"));
        if(intent.hasExtra("openFileIsInCache"))
            newIntent.putExtra("openFileIsInCache", intent.getStringExtra("openFileIsInCache"));
        if(intent.hasExtra("importCount"))
            newIntent.putExtra("importCount", intent.getIntExtra("importCount", 0));
        if(intent.hasExtra("importList"))
            newIntent.putCharSequenceArrayListExtra("importList", intent.getCharSequenceArrayListExtra("importList"));
        startActivity(newIntent);

        LunchActivity.this.finish();
    }

    //权限申请
    //=================

    private final String[] permissions = {
            Manifest.permission.READ_EXTERNAL_STORAGE,
            Manifest.permission.WRITE_EXTERNAL_STORAGE
    };

    private boolean checkPermission() {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            int i = checkSelfPermission(permissions[0]);
            // 权限是否已经 授权 GRANTED---授权  DINIED---拒绝
            if (i != PackageManager.PERMISSION_GRANTED) {
                // 如果没有授予该权限，就去提示用户请求
                showDialogTipUserRequestPermission();
                return false;
            }
        }
        return true;
    }

    // 提示用户该请求权限的弹出框
    private void showDialogTipUserRequestPermission() {
        new CommonDialog(this)
                .setImageResource(R.drawable.ic_per_storage)
                .setTitle(R.string.text_no_storage_permission)
                .setMessage(R.string.text_storage_permission_usage)
                .setPositive(R.string.action_open_now)
                .setNegative(R.string.action_cancel_and_quit)
                .setOnResult((b, dialog) -> {
                    if(b == CommonDialog.BUTTON_POSITIVE) {
                        startRequestPermission();
                        return true;
                    } else if(b == CommonDialog.BUTTON_NEGATIVE) {
                        finish();
                        return true;
                    }
                    return false;
                })
                .setCancelable(false)
                .show();
    }
    // 开始提交请求权限
    private void startRequestPermission() { requestPermissions(this.permissions, REQUEST_CODE); }
    // 提示用户去应用设置界面手动开启权限
    private void showDialogTipUserGoToAppSettings() {

        // 跳转到应用设置界面
        new CommonDialog(this)
                .setCancelable(false)
                .setImageResource(R.drawable.ic_warning)
                .setTitle(R.string.text_denied_storage_permission)
                .setMessage(R.string.text_storage_permission_open_intro)
                .setPositive(R.string.action_go_and_set)
                .setNegative(R.string.action_cancel_and_quit)
                .setOnResult((b, dialog) -> {
                    if(b == CommonDialog.BUTTON_POSITIVE) {
                        // 跳转到应用设置界面
                        goToAppSetting();
                        return true;
                    } else if(b == CommonDialog.BUTTON_NEGATIVE) {
                        finish();
                        return true;
                    }
                    return false;
                })
                .show();
    }
    // 跳转到当前应用的设置界面
    private void goToAppSetting() {
        Intent intent = new Intent();

        intent.setAction(Settings.ACTION_APPLICATION_DETAILS_SETTINGS);
        Uri uri = Uri.fromParts("package", getPackageName(), null);
        intent.setData(uri);

        startActivityForResult(intent, REQUEST_CODE_SETTINGS);
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        if (requestCode == REQUEST_CODE) {
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
                if (grantResults[0] != PackageManager.PERMISSION_GRANTED) {
                    // 判断用户是否 点击了不再提醒。(检测该权限是否还可以申请)
                    boolean b = shouldShowRequestPermissionRationale(permissions[0]);
                    if (!b) {
                        // 用户还是想用我的 APP 的
                        // 提示用户去应用设置界面手动开启权限
                        showDialogTipUserGoToAppSettings();
                    } else
                        finish();
                }else runMainActivity();
            }
        } else if (requestCode == REQUEST_CODE_SETTINGS) {
            runPermissionAndAgreement();
        }
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
    }

}
