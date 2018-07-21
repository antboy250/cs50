import os

import io
from cs50 import SQL, eprint
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Ensure environment variable is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    return apology("TODO")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        stockinfo = lookup(request.form.get("symbol"))
        numshares = float(request.form.get("numshares"))
        if not stockinfo:
            return apology("Stock Symbol or Number of Shares invalid", 403)
        price = float(stockinfo["price"])
        eprint(session["user_id"])
        rows = db.execute("SELECT cash FROM users WHERE id = :cid;", cid=session["user_id"])
        oldcash = float(rows[0]["cash"])
        print(oldcash)
        totalprice = price * numshares
        newcash = oldcash - totalprice
        print(newcash)
        db.execute("UPDATE users SET cash = :c WHERE id = :sid;", c=newcash, sid=session["user_id"])
        db.execute("INSERT into userstocks ('id', 'stock', 'price', 'numshares', 'date') VALUES (:uid, :sym, :total, :shares, strftime('%s','now'));", uid=session["user_id"], sym=stockinfo["symbol"], total=totalprice, shares=int(numshares))
        return render_template("index.html")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        stockinfo = lookup(request.form.get("symbol"))
        if not stockinfo:
            return apology("Symbol field is blank or does not exist", 403)
        price = stockinfo["price"]
        return render_template("quoted.html", price=price, symbol=request.form.get("symbol"))
    else:
        return render_template("quote.html")



@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password") or not request.form.get("confirmation") or (request.form.get("password") != request.form.get("confirmation")):
            return apology("Did not provide password or passwords do not match!", 403)

        #Hashing the password
        hashedpass = generate_password_hash(request.form.get("password"))

        #Registering User if all checks passed
        db.execute("INSERT into users ('username', 'hash') VALUES (:u, :h);", u=request.form.get("username"), h=hashedpass)

        return render_template("login.html")


    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    return apology("TODO")


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
