/*
 * Copyright (c) 2015-present, Parse, LLC.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */
package com.parse.starter;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import com.parse.LogInCallback;
import com.parse.ParseAnalytics;
import com.parse.ParseException;
import com.parse.ParseUser;


public class LogInActivity extends ActionBarActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);

        ParseAnalytics.trackAppOpenedInBackground(getIntent());

//    ParseObject testObject = new ParseObject("TestObject");
//    testObject.put("foo", "bar");
//    testObject.saveInBackground(new SaveCallback() {
//      @Override
//      public void done(ParseException e) {
//        if(e == null) {
//          Toast.makeText(getApplicationContext(), "Success", Toast.LENGTH_LONG).show();
//
//          ParseQuery<ParseObject> query = ParseQuery.getQuery("TestObject");
//          query.findInBackground(new FindCallback<ParseObject>() {
//            @Override
//            public void done(List<ParseObject> list, ParseException e) {
//              String msg = "Retrieved " + list.size() + " TestObject";
//              Toast.makeText(getApplicationContext(), msg, Toast.LENGTH_LONG).show();
//            }
//          });
//        } else {
//          Toast.makeText(getApplicationContext(), e.getMessage(), Toast.LENGTH_LONG).show();
//        }
//      }
//    });

        addAllEvent();
    }
    private void signUpEvent()
    {
        Button btSignUp = (Button) findViewById(R.id.btSignUp);
        btSignUp.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(getApplicationContext(), SignUpActivity.class);
                startActivity(intent);
            }
        });
    }
    private void logInRequest()
    {
        EditText etId = (EditText) findViewById(R.id.etId);
        EditText etPw = (EditText) findViewById(R.id.etPw);
        ParseUser.logOut();
        ParseUser.logInInBackground(etId.getText().toString(), etPw.getText().toString(), new LogInCallback() {
            @Override
            public void done(ParseUser user, ParseException e) {
                if(e == null)
                {
                    Toast.makeText(getApplicationContext(), "LogIn Complete", Toast.LENGTH_LONG).show();
                    Intent intent = new Intent(getApplicationContext(), MainActivity.class);
                    startActivity(intent);
                }
                else
                {
                    Toast.makeText(getApplicationContext(), e.getMessage(), Toast.LENGTH_LONG).show();
                }
            }
        });
    }
    private void logInEvent()
    {
        Button btLogIn = (Button) findViewById(R.id.btLogin);
        btLogIn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                logInRequest();
            }
        });
    }
    private void addAllEvent()
    {
        signUpEvent();
        logInEvent();
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
