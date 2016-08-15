/*
 * Copyright (c) 2015-present, Parse, LLC.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */
package com.parse.starter;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.Toast;

import com.parse.FindCallback;
import com.parse.ParseAnalytics;
import com.parse.ParseException;
import com.parse.ParseObject;
import com.parse.ParseQuery;
import com.parse.SaveCallback;

import java.net.URL;
import java.util.List;


public class MainActivity extends ActionBarActivity {

  private Bitmap bmOn;
  private Bitmap bmOff;
  private ImageView ivBulb;
  private EditText  etId;
  private EditText  etRoom;
  private String plugClassName = "iot_switch";
  private String defaultUsrId = "test_1";
  private String defaultRoomName = "room_1";

  @Override
  protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    setContentView(R.layout.activity_main);

    ParseAnalytics.trackAppOpenedInBackground(getIntent());
    ivBulb = (ImageView)findViewById(R.id.ivBulb);
    etId = (EditText)findViewById(R.id.etUsrId);
    etId.setText(defaultUsrId);
    etRoom = (EditText)findViewById(R.id.etRoomName);
    etRoom.setText(defaultRoomName);
    new DownLoadBitmap().execute();
  }

  class DownLoadBitmap extends AsyncTask<Void,Void,Void>
  {

    @Override
    protected Void doInBackground(Void... params) {
      try {
        URL onUrl = new URL("https://bit.ly/plugbulbon");
        bmOn = BitmapFactory.decodeStream(onUrl.openStream());
        URL offUrl = new URL("https://bit.ly/plugbulboff");
        bmOff = BitmapFactory.decodeStream(offUrl.openStream());
        getData();
      }
      catch (Exception e)
      {
        e.getStackTrace();
      }
      return null;
    }

  }
  private void getData()
  {
    ParseQuery<ParseObject> query = ParseQuery.getQuery(plugClassName);
    query.whereEqualTo("usrId",etId.getText().toString());
    query.whereEqualTo("locate",etRoom.getText().toString());
    query.setLimit(1);
    query.addDescendingOrder("updatedAt");
    query.findInBackground(new FindCallback<ParseObject>() {
      @Override
      public void done(List<ParseObject> list, ParseException e) {
        if(list.size() > 0)
          for (ParseObject obj : list) {
            changeImg(obj.getInt("state"));
          }
      }
    });
  }
  private void changeImg(int state)
  {
    if(state==1){
      ivBulb.setImageBitmap(bmOn);
    }
    else{
      ivBulb.setImageBitmap(bmOff);
    }
  }


  public void btOnClick(View view)
  {
    sendRequest(1);
  }
  public void btOffClick(View view)
  {
    sendRequest(0);
  }
  private void sendRequest(final int state)
  {
    ParseObject obj = new ParseObject(plugClassName);
    obj.put("usrId",etId.getText().toString());
    obj.put("locate",etRoom.getText().toString());
    obj.put("sw_rqst",1);
    obj.put("state",state);
    obj.saveInBackground(new SaveCallback() {
      @Override
      public void done(ParseException e) {
        if (e == null) {
          Toast.makeText(getApplicationContext(), " save completed", Toast.LENGTH_LONG).show();
          changeImg(state);
        } else {
          Toast.makeText(getApplicationContext(), e.getMessage(), Toast.LENGTH_LONG).show();
        }
      }
    });
  }
  @Override
  public boolean onCreateOptionsMenu(Menu menu) {
    // Inflate the menu; this adds items to the action bar if it is present.
    getMenuInflater().inflate(R.menu.menu_main, menu);
    return true;
  }

  @Override
  public boolean onOptionsItemSelected(MenuItem item) {
    // Handle action bar item clicks here. The action bar will
    // automatically handle clicks on the Home/Up button, so long
    // as you specify a parent activity in AndroidManifest.xml.
    int id = item.getItemId();

    //noinspection SimplifiableIfStatement
    if (id == R.id.action_settings) {
      return true;
    }

    return super.onOptionsItemSelected(item);
  }
}
