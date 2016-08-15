package com.parse.starter;

import android.content.Intent;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.text.method.ScrollingMovementMethod;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import com.parse.FindCallback;
import com.parse.LogOutCallback;
import com.parse.ParseException;
import com.parse.ParseObject;
import com.parse.ParseQuery;
import com.parse.ParseUser;
import com.parse.SaveCallback;

import org.w3c.dom.Text;

import java.util.List;


public class MainActivity extends ActionBarActivity {

    private String logClassName = "ClickLog";
    private String logMsgKey = "msg";
    private TextView tvLog;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        tvLog = (TextView)findViewById(R.id.tvLog);
        tvLog.setMovementMethod(new ScrollingMovementMethod());
        TextView idView = (TextView)findViewById(R.id.tvMainId);
        idView.setText("Welcome : "+ParseUser.getCurrentUser().getUsername() + "! ");

        refreshClickLog();
    }

    private void refreshClickLog()
    {
        ParseQuery<ParseObject> query = ParseQuery.getQuery(logClassName);
        query.findInBackground(new FindCallback<ParseObject>() {
            @Override
            public void done(List<ParseObject> list, ParseException e) {
                tvLog.setText("");
                for (ParseObject obj : list) {
                    tvLog.append(obj.get(logMsgKey).toString() + "\n");
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
    public void btLogoutClick(View view) {
        ParseUser.logOutInBackground(new LogOutCallback() {
            @Override
            public void done(ParseException e) {
                if(e == null){
                    Toast.makeText(getApplicationContext(), "Logout Completed", Toast.LENGTH_LONG).show();
                    Intent intent = new Intent(getApplicationContext(), LogInActivity.class);
                    intent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
                    startActivity(intent);
                } else {
                    Toast.makeText(getApplicationContext(), e.getMessage(), Toast.LENGTH_LONG).show();
                }

            }
        });
    }
    public void btClick(View view) {
        final String titleText = ((Button)view).getText().toString();
        tvLog.append(titleText + "Clicked. \n");


        ParseObject obj = new ParseObject(logClassName);
        obj.put(logMsgKey, titleText);

        obj.saveInBackground(new SaveCallback() {
          @Override
          public void done(ParseException e) {
            if(e == null) {
              Toast.makeText(getApplicationContext(), titleText + " save completed", Toast.LENGTH_LONG).show();
            } else {
              Toast.makeText(getApplicationContext(), e.getMessage(), Toast.LENGTH_LONG).show();
            }
          }
        });

    }
}
