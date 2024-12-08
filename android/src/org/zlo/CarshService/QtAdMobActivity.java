package org.zlo.CarshService;

import android.os.Environment;
import android.os.Bundle;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.ArrayList;
import org.qtproject.qt.android.bindings.QtActivity;
import android.app.Activity;
import android.net.Uri;
import android.util.Log;
import android.widget.Toast;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.ResultSetMetaData;
import java.sql.SQLException;
import java.sql.SQLTimeoutException;
import java.sql.Statement;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageManager;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;
import android.Manifest;
import android.app.AlertDialog;
import android.content.DialogInterface;

public class QtAdMobActivity extends QtActivity {

   //private RelativeLayout.LayoutParams mainLayoutParams = null;
   private Connection connection;
   private Statement statement;
   private String strConnectedHost;

   private static final int CarshService_PERMISSION_CAMERA  = 1004;

   private static final int PICKFILEIMG_RESULT_CODE = 1001;


   final QtAdMobActivity self = this;

    public boolean isDbConnected(Connection con) {
       try {
           return con != null && !con.isClosed();
       } catch (SQLException ignored) {}

       return false;
   }


    public int OpenServerBD(String host)
    {
       Log.d("LogAD","ConnectToServer called ");

       //String jdbcUrl = "jdbc:postgresql://"+host+":5432/CarshService";
       String jdbcUrl = "jdbc:postgresql://188.243.205.147:5432/CarshService";
       String username = "postgres";
       String password = "VthctltcWKR200";

       if( (host!=strConnectedHost) || (!isDbConnected(connection)))
       {

            try
            {
                connection = DriverManager.getConnection(jdbcUrl, username, password);

              //  statement = connection.createStatement();
            }
            catch (SQLException e)
            {
                e.printStackTrace();
                return 0;
            }
        }

        strConnectedHost = host;

        return 1;
    }

    public int CloseServerBD()
    {
        try
        {
           // statement.close();
            connection.close();

        }
        catch (SQLException e)
        {
            e.printStackTrace();
        }

        return 1;
    }

    public int getStatusBarHeight() {
          int result = 0;
          int resourceId = getResources().getIdentifier("status_bar_height", "dimen", "android");
          if (resourceId > 0) {
              result = getResources().getDimensionPixelSize(resourceId);
          }
          return result;
    }

    public int getNavigationBarHeight() {
        int resourceId = getResources().getIdentifier("navigation_bar_height", "dimen", "android");
        if (resourceId > 0) {
            return getResources().getDimensionPixelSize(resourceId);
        }
        return 0;
    }

    public int GetNaviPanelHegith()
    {
       return  (int)(getNavigationBarHeight()/getResources().getDisplayMetrics().density);
    }

    public int execQueryUpdate(String strQuery)
    {
        try
        {
            if(!connection.isValid(0))  OpenServerBD("String host");
            //Сделали препаре, а не сразу вызов, что бы задать результату свойство ходибельности туда-обратно что бы посчитать количество строк в результате
            //Log.d("execQueryUpdate", "queru = " + strQuery);
            PreparedStatement ps = connection.prepareStatement(strQuery , ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
            ps.executeUpdate();

            ps.close();

            return 1;

        }
        catch (SQLException e)
        {
            e.printStackTrace();
        }

        return 0;
    }


    public String[] execQuery(String strQuery)
    {
        try
        {
            if(!connection.isValid(0))  OpenServerBD("String host");
            //Сделали препаре, а не сразу вызов, что бы задать результату свойство ходибельности туда-обратно что бы посчитать количество строк в результате

            PreparedStatement ps = connection.prepareStatement(strQuery , ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
            ResultSet resultSet = ps.executeQuery();

            //Log.d("execQuery", "queru = " + strQuery);

            //Выделим память под результат, для этого узнаём сколько строк (сходим в конец набора, получим номер последней строки, вернёмся обратно
            resultSet.last();
            String [] retVal = new String[resultSet.getRow()];
            resultSet.beforeFirst();

            ResultSetMetaData rsmd = resultSet.getMetaData();

            int iColumnCount = rsmd.getColumnCount();

            //Заполним результирующий массив
            int iResCounter=0;
            while (resultSet.next())
            {
                int iColumnCounter = 1;
                String currStrRowResult = "";
                while (iColumnCounter <= iColumnCount)
                {
                    currStrRowResult = currStrRowResult + resultSet.getString(iColumnCounter) + "##--**";

                    iColumnCounter++;
                }
               // Log.d("execQuery", "currStrRowResult = " + currStrRowResult);
                retVal[iResCounter] = currStrRowResult;

                iResCounter++;
            }
            resultSet.close();

            ps.close();

            return retVal;

        }
        catch (SQLException e)
        {
            e.printStackTrace();
        }

        return null;
    }

    @Override
    public void onRequestPermissionsResult(int requestCode,String permissions[],int[] grantResults)
    {
        switch (requestCode) {
           case CarshService_PERMISSION_CAMERA:
                 if (grantResults.length > 0 && grantResults[0] == PackageManager.PERMISSION_GRANTED)
                 {
                      Toast.makeText(self, "Камера. Разрешение предоставлено!", Toast.LENGTH_SHORT).show();
                 }
                 else
                 {
                      Toast.makeText(self, "Камера. Разрешение НЕ предоставлено!", Toast.LENGTH_SHORT).show();
                 }
                 break;
          }
    }

    private void requestPermission(String permissionName, int permissionRequestCode)
    {
        Log.d("requestPermissions: ", " permissionName=" + permissionName);
        ActivityCompat.requestPermissions(this,new String[]{permissionName}, permissionRequestCode);
    }

    private void showExplanation(String title, String message, final String permission, final int permissionRequestCode)
    {
         runOnUiThread(new Runnable()
         {
              public void run()
              {

                       AlertDialog.Builder builder = new AlertDialog.Builder(self);
                       builder.setTitle(title)
                              .setMessage(message)
                              .setPositiveButton(android.R.string.ok, new DialogInterface.OnClickListener()
                              {
                                         public void onClick(DialogInterface dialog, int id)
                                         {
                                             requestPermission(permission, permissionRequestCode);
                                         }
                              });
                              builder.create().show();
              }
         });
    }


    public int IsCameraPremissionAndRequest(Context context)
    {

         int permissionCheck = ContextCompat.checkSelfPermission(this, Manifest.permission.CAMERA);

         if (permissionCheck != PackageManager.PERMISSION_GRANTED)
         {
             if (ActivityCompat.shouldShowRequestPermissionRationale(this, Manifest.permission.CAMERA))
             {
                  showExplanation("Для установки напоминания приложению требуется разрешение \"Уведомления\".", "Планы", Manifest.permission.CAMERA, CarshService_PERMISSION_CAMERA);

                  return 0;
             }
             else
             {
                  requestPermission(Manifest.permission.CAMERA, CarshService_PERMISSION_CAMERA);

                  return 0;
             }
         }
         else
         {
             return 1;
         }
    }


/*работает, оставлено на память, т.к. лень делать вызов сигналов из джавы, реализовано всё тоже самое непосредственно в с++*/
    // public int GetPhoto()
    // {



    //         // Intent i = new Intent(Intent.ACTION_PICK,
    //         // android.provider.MediaStore.Images.Media.EXTERNAL_CONTENT_URI);

    //         // startActivityForResult(i.createChooser(i, "Select Picture"), PICK_IMAGE);

    //         Intent chooseFile;
    //         Intent intent;
    //         chooseFile = new Intent(Intent.ACTION_GET_CONTENT);
    //         chooseFile.setType("image/*");
    //         chooseFile.putExtra(Intent.EXTRA_ALLOW_MULTIPLE, true);
    //         intent = Intent.createChooser(chooseFile, "Choose a file");
    //         startActivityForResult(intent, PICKFILEIMG_RESULT_CODE);

    //         return( 0 );
    // }


    // @Override
    // public void onActivityResult(int requestCode, int resultCode, Intent data) {
    //     super.onActivityResult(requestCode, resultCode, data);
    //     if(requestCode == PICKFILEIMG_RESULT_CODE) {
    //        if(null != data) { // checking empty selection
    //           if(null != data.getClipData()) { // checking multiple selection or not
    //              for(int i = 0; i < data.getClipData().getItemCount(); i++) {
    //                 Uri uri = data.getClipData().getItemAt(i).getUri();
    //                 Log.d("onActivityResult Select PicsUri =  ", uri.toString());
    //              }
    //           } else {
    //              Uri uri = data.getData();
    //           }
    //        }
    //     }
    //  }


    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);


    }

    @Override
    public void onResume() {
       // Log.d("LogAD", "QtAdMobActivity onResume() ");
        super.onResume();

    }
    @Override
    public void onPause() {
      //  Log.d("LogAD", "QtAdMobActivity onPause() ");
        super.onPause();


    }
    @Override
    public void onDestroy() {
      //  Log.d("LogAD", "QtAdMobActivity onDestroy() ");
        super.onDestroy();


    }

}
