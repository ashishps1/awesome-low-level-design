from auction_service import AuctionService
from user import User
from auction import Auction
from bid import Bid
from typing import List
from decimal import Decimal
from datetime import datetime, timedelta
import time

class AuctionSystemDemo:
    @staticmethod
    def main():
        auction_service = AuctionService.get_instance()

        alice = auction_service.create_user("Alice")
        bob = auction_service.create_user("Bob")
        carol = auction_service.create_user("Carol")

        print("=============================================")
        print("        Online Auction System Demo           ")
        print("=============================================")

        end_time = datetime.now() + timedelta(seconds=10)
        laptop_auction = auction_service.create_auction(
            "Vintage Laptop",
            "A rare 1990s laptop, in working condition.",
            Decimal("100.00"),
            end_time
        )
        print()

        try:
            auction_service.place_bid(laptop_auction.get_id(), alice.get_id(), Decimal("110.00"))
            time.sleep(0.5)

            auction_service.place_bid(laptop_auction.get_id(), bob.get_id(), Decimal("120.00"))
            time.sleep(0.5)

            auction_service.place_bid(laptop_auction.get_id(), carol.get_id(), Decimal("125.00"))
            time.sleep(0.5)

            auction_service.place_bid(laptop_auction.get_id(), alice.get_id(), Decimal("150.00"))

            print("\n--- Waiting for auction to end automatically... ---")
            time.sleep(2)
        except Exception as e:
            print(f"An error occurred during bidding: {e}")

        print("\n--- Post-Auction Information ---")
        ended_auction = auction_service.get_auction(laptop_auction.get_id())

        if ended_auction.get_winning_bid() is not None:
            print(f"Final Winner: {ended_auction.get_winning_bid().get_bidder().get_name()}")
            print(f"Winning Price: ${ended_auction.get_winning_bid().get_amount():.2f}")
        else:
            print("The auction ended with no winner.")

        print("\nFull Bid History:")
        for bid in ended_auction.get_bid_history():
            print(bid)

        print("\n--- Attempting to bid on an ended auction ---")
        try:
            auction_service.place_bid(laptop_auction.get_id(), bob.get_id(), Decimal("200.00"))
        except Exception as e:
            print(f"CAUGHT EXPECTED ERROR: {e}")

        auction_service.shutdown()


if __name__ == "__main__":
    AuctionSystemDemo.main()