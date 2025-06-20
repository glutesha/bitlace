<script lang="ts">
    import { onMount, onDestroy } from "svelte";
    import { battery, get_battery } from "../battery";

    let interval: number;

    onMount(async () => {
        await get_battery();
        interval = setInterval(() => {
            get_battery();
        }, 60000);
    });

    onDestroy(() => {
        clearInterval(interval);
    });

</script>

<div class="p-4 absolute">
    <div class="flex flex-row gap-0.5 justify-center items-center">
        <div class="w-17 h-6 relative rounded-md bg-neutral-900 outline-3 outline-offset-2 outline-lime-900 shadow-xl shadow-black">
            <p class="absolute inset-0 flex items-center justify-center text-white font-bold text-md z-10">{$battery}%</p>
            <div class="bg-lime-600 h-6 text-xs font-medium text-white text-center p-1 leading-none rounded-md" style="width: {$battery}%"></div>
        </div>
        <div class="w-2 h-5 rounded-md bg-lime-900 shadow-md shadow-black"></div>
    </div>
</div>