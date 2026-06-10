package antik.modz;

import android.Manifest;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.graphics.Color;
import android.graphics.drawable.GradientDrawable;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.provider.Settings;
import android.widget.TextView;
import android.widget.Toast;
import antik.modz.modmenu.FloatingModMenuService;

public class MainActivity extends Activity {

    public String GameActivity = "com.unity3d.player.UnityPlayerActivity";
    public boolean hasLaunched = false;

    static {
        System.loadLibrary("logic");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Start(this);

        if (!hasLaunched) {
            try {
                MainActivity.this.startActivity(new Intent(MainActivity.this, Class.forName(MainActivity.this.GameActivity)));
                hasLaunched = true;
            } catch (ClassNotFoundException e) {
                e.printStackTrace();
                return;
            }
        }
    }

    private static void MyToast(Context context, String text) {
        TextView textView = new TextView(context);
        textView.setText(text);
        textView.setPadding(20, 10, 20, 10);
        textView.setTextColor(Color.parseColor("#FF00FFFF")); // Toast Text Color
        GradientDrawable gd = new GradientDrawable();
        gd.setColor(Color.parseColor("#FF0A0A0A")); // Background Color
        gd.setCornerRadii(new float[]{30, 30, 0, 0, 30, 30, 0, 0});
        gd.setStroke(3, Color.parseColor("#FF00FFFF")); // Stroke Color #FFBAC24A
        textView.setBackground(gd);

        Toast toast = Toast.makeText(context, null, Toast.LENGTH_LONG);
        toast.setView(textView);
        toast.show();
    }

	public static void Start(final Activity context) {
		// 1. Overlay permission
		if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M && !Settings.canDrawOverlays(context)) {
			MyToast(context, "Overlay permission is required in order to show mod menu. Restart the game after you allow permission");
			MyToast(context, "Overlay permission is required in order to show mod menu. Restart the game after you allow permission");
			context.startActivity(new Intent("android.settings.action.MANAGE_OVERLAY_PERMISSION",
											 Uri.parse("package:" + context.getPackageName())));
			new Handler().postDelayed(new Runnable() {
					@Override
					public void run() {
						System.exit(1);
					}
				}, 5000);
			return;
		}

		// 2. Android 6-10
		if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M &&
			Build.VERSION.SDK_INT < Build.VERSION_CODES.R) {
			if (context.checkSelfPermission(Manifest.permission.READ_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED ||
				context.checkSelfPermission(Manifest.permission.WRITE_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED) {
				context.requestPermissions(new String[]{
											   Manifest.permission.READ_EXTERNAL_STORAGE,
											   Manifest.permission.WRITE_EXTERNAL_STORAGE
										   }, 1);
			}
		}

		// 3. Android 11-12L (MANAGE_EXTERNAL_STORAGE)
		if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.R &&
			Build.VERSION.SDK_INT < 32) {
			if (!Environment.isExternalStorageManager()) {
				context.startActivity(new Intent(
										  Settings.ACTION_MANAGE_APP_ALL_FILES_ACCESS_PERMISSION,
										  Uri.parse("package:" + context.getPackageName())
									  ));
			}
		}

		// 4. Android 13+ (READ_MEDIA_*)
		if (Build.VERSION.SDK_INT >= 33) {
			if (context.checkSelfPermission("android.permission.READ_MEDIA_IMAGES") != PackageManager.PERMISSION_GRANTED ||
				context.checkSelfPermission("android.permission.READ_MEDIA_VIDEO") != PackageManager.PERMISSION_GRANTED ||
				context.checkSelfPermission("android.permission.READ_MEDIA_AUDIO") != PackageManager.PERMISSION_GRANTED) {
				context.requestPermissions(new String[]{
											   "android.permission.READ_MEDIA_IMAGES",
											   "android.permission.READ_MEDIA_VIDEO",
											   "android.permission.READ_MEDIA_AUDIO"
										   }, 2);
			}
		}

		// 5. Run Server
		new Handler().postDelayed(new Runnable() {
				@Override
				public void run() {
					context.startService(new Intent(context, FloatingModMenuService.class));
				}
			}, 500);
	}
}
